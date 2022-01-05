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
  // waitpid(2)
  // #include <sys/wait.h>
  // wait for process to change state，等待进程更改状态
  // 父进程调用waitpid()会被阻塞，第1个参数可以设置等待对象的范围
  pid_t exit_pid = waitpid(-1, &status, 0);
  printf("[debug]:parent,waitpid(),exit_pid=%d,status=%d\r\n", exit_pid, status);

  // WIFEXITED(status)，宏函数，返回子进程是不是正常退出，如果是，它会返回一个非零值
  if (WIFEXITED(status)) {
    // WEXITSTATUS(status)，宏函数，当WIFEXITED返回非零值时，可以用这个宏来提取子进程的返回值
    // 如果子进程调用exit(5)退出，WEXITSTATUS(status)就会返回5
    // 如果进程不是正常退出的，即WIFEXITED(status)返回0时，这个值无意义
    printf("[error]:WIFEXITED()!=0,WEXITSTATUS()=%d\r\n", WEXITSTATUS(status));
  }

  while (1) {
    printf("[debug]:parent,getpid()=%d\r\n", getpid());
    sleep(2);
  }

  return 0;
}