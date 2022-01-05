#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

// 信号处理函数
void signal_handler(int signal_no) {
  printf("[info]:signal_no=%d\r\n", signal_no);
}

int main() {
  printf("[debug]:parent,getpid()=%d\r\n", getpid());
  pid_t pid = fork();

  if (pid == -1) {
    printf("[error]:fock(),failed\r\n");
    printf("[error]:errno=%d,errstr%s\r\n", errno, strerror(errno));
    exit(0);
  }

  if (pid == 0) {
    signal(SIGSTOP, signal_handler);
    signal(SIGCONT, signal_handler);
    while (1) {
      printf("[debug]:child,getpid=%d\r\n", getpid());
      sleep(2);
    }
  }

  int status;
  pid_t exit_pid = waitpid(-1, &status, 0);
  printf("[debug]:parent,waitpid(),exit_pid=%d,status=%d\r\n", exit_pid, status);
  if (WIFSIGNALED(status)) {
    printf("[error]:WIFSIGNALED()!=0,WTERMSIG()=%d\n", WTERMSIG(status));
  }

  while (1) {
    printf("[debug]:parent,getpid()=%d\r\n", getpid());
    sleep(2);
  }

  return 0;
}