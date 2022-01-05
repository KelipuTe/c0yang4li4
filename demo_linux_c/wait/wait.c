#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
  printf("[debug]:parent,getpid()=%d\r\n", getpid());
  pid_t pid = fork();

  if (pid == -1) {
    printf("[error]:fock(),failed\r\n");
    printf("[error]:errno=%d,errstr%s\r\n", errno, strerror(errno));
    exit(0);
  }

  if (pid == 0) {
    printf("[debug]:child,getpid=%d\r\n", getpid());
    exit(0);
  }

  int status;
  // wait(2)
  // #include <sys/wait.h>
  // wait for process to change state，等待进程更改状态
  // 父进程调用wait()会被阻塞，直到有子进程退出
  // wait()返回的exit_pid是退出的子进程的pid，status是子进程退出的状态码
  // wait(&status)和waitpid(-1, &status, 0)是等效的
  pid_t exit_pid = wait(&status);
  printf("[debug]:parent,wait(),exit_pid=%d,status=%d\r\n", exit_pid, status);

  while (1) {
    printf("[debug]:parent,getpid()=%d\r\n", getpid());
    sleep(2);
  }

  return 0;
}