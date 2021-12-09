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
    while (1) {
      printf("child,pid=%d\r\n", getpid());
      sleep(2);
    }
  }

  int status;
  pid_t exit_pid = waitpid(-1, &status, 0);
  printf("child exit,pid=%d,exit status=%d\r\n", exit_pid, status);

  //宏函数WIFSIGNALED(status)，返回子进程是不是被信号终止
  if (WIFSIGNALED(status)) {
    printf("child terminated by a signal,exit status=%d\n", WTERMSIG(status));
  }

  while (1) {
    printf("parent,process,pid=%d\r\n", pid);
    sleep(2);
  }

  return 0;
}