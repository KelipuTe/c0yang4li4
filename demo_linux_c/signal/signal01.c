#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void signal_handler(int signo) {
  printf("signo=%d\r\n", signo);
}

int main() {

  printf("pid=%d\r\n", getpid());

  signal(SIGINT, signal_handler); //收到SIGINT时，执行对应的信号处理函数
  signal(SIGUSR1, SIG_IGN);       //收到SIGUSR1时，执行忽略动作
  signal(SIGUSR2, SIG_DFL);       //收到SIGUSR2时，执行默认动作

  while (1) {
    printf("pid=%d\r\n", getpid());
    sleep(2);
  }

  return 0;
}