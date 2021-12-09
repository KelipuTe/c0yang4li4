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
  pid_t exit_pid = waitpid(-1, &status, 0);
  printf("child exit,pid=%d,exit status=%d\r\n", exit_pid, status);

  //宏函数WIFEXITED(status)，返回子进程是不是正常退出
  //宏函数WEXITSTATUS(status)，返回
  if (WIFEXITED(status)) {
    printf("child terminated normally,exit status=%d\r\n", WEXITSTATUS(status));
  }

  while (1) {
    printf("parent,process,pid=%d\r\n", pid);
    sleep(2);
  }

  return 0;
}