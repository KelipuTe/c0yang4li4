#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void signalHandler(int signalNO) {
  printf("signalNO=%d\n", signalNO);
}

int main() {
  printf("parent,getpid()=%d\n", getpid());
  
  pid_t pid = fork();

  if (pid == -1) {
    printf("fock(),failed\n");
    printf("errno=%d,strerror=%s\n", errno, strerror(errno));
    exit(0);
  }

  if (pid == 0) {
    signal(SIGSTOP, signalHandler);
    signal(SIGCONT, signalHandler);
    while (1) {
      printf("child,getpid=%d\n", getpid());
      sleep(2);
    }
  }

  int status;
  pid_t exitPid = waitpid(-1, &status, 0);
  printf("parent,waitpid(),exitPid=%d,status=%d\r\n", exitPid, status);
  // WIFSIGNALED(status)，宏函数，返回子进程是不是被信号终止，如果是，它会返回一个非零值
  if (WIFSIGNALED(status)) {
    // WTERMSIG(status)，宏函数，当WIFSIGNALED(status)返回非零值时，可以用这个宏来提取信号的编号
    printf("parent,WIFSIGNALED()!=0,WTERMSIG()=%d\n", WTERMSIG(status));
  }

  while (1) {
    printf("parent,getpid()=%d\n", getpid());
    sleep(2);
  }

  return 0;
}