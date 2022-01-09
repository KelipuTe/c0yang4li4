#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// 信号处理函数
void signal_handler(int signal_no) {
  printf("[info]:signal_no=%d\r\n", signal_no);
}

int main() {
  printf("[debug]:getpid()=%d\r\n", getpid());

  // signal(2)
  // #include <signal.h>
  // ANSI C signal handling，给信号量定义一个处理函数
  //收到SIGINT时，执行处理函数，signal_handler
  signal(SIGINT, signal_handler);
  //收到SIGUSR1时，执行忽略动作，SIG_IGN
  signal(SIGUSR1, SIG_IGN);
  //收到SIGUSR2时，执行默认动作，SIG_DFL
  signal(SIGUSR2, SIG_DFL);

  while (1) {
    printf("[debug]:getpid()=%d\r\n", getpid());
    sleep(2);
  }

  return 0;
}