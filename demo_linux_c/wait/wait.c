#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

int main() {

  pid_t pid = fork();

  if (pid == -1) {
    printf("fock error\r\n");
    exit(0);
  }

  if (pid == 0) {
    printf("child,pid=%d\r\n", getpid());
    exit(0);
  }

  int status;
  pid_t exit_pid = wait(&status);
  //系统函数wait()会阻塞父进程，直到有子进程退出。
  //exit_pid时退出的子进程的pid，status是子进程退出的状态码
  //wait(&status)和waitpid(-1, &status, 0)是等效的
  printf("child exit,pid=%d,exit status=%d\r\n", exit_pid, status);

  while (1) {
    printf("parent,process,pid=%d\r\n", pid);
    sleep(2);
  }

  return 0;
}