#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void signalHandler(int signalNO) {
  printf("signalNO=%d\n", signalNO);
}

int main() {
  printf("[debug]:getpid()=%d\n", getpid());

  // 收到 SIGUSR1 时，执行默认动作，SIG_DFL
  signal(SIGUSR1, SIG_DFL);
  // 收到 SIGUSR2 时，执行忽略动作，SIG_IGN
  signal(SIGUSR2, SIG_IGN);
  // 收到 SIGINT 时，执行处理函数，signalHandler
  signal(SIGINT, signalHandler);

  while (1) {
    printf("[debug]:getpid()=%d\n", getpid());
    sleep(2);
  }

  return 0;
}