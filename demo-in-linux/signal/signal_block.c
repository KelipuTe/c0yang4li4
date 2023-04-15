#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// 信号处理函数
void signal_handler(int signal_no) {
  printf("[info]:signal_no=%d\n", signal_no);
}

int main() {
  printf("[debug]:getpid()=%d\n", getpid());

  // 信号集
  sigset_t blockSet;
  // 将信号集设置为空
  sigemptyset(&blockSet);
  // 设置 SIGINT 信号
  sigaddset(&blockSet, SIGINT);
  // 设置信号集为阻塞，进程收到信号后，信号会被阻塞
  sigprocmask(SIG_BLOCK, &blockSet, NULL);

  struct sigaction action;
  action.sa_handler = signal_handler;
  action.sa_flags = SA_RESTART;

  if (sigaction(SIGINT, &action, NULL)) {
    printf("[debug]:sigaction() fail\n");
  }

  sigset_t pendingSet;
  sigemptyset(&pendingSet);
  int j = 0;
  while (1) {
    // 获取被阻塞的信号
    sigpending(&pendingSet);

    // 格式化输出
    printf("[info]:pendingSet:");
    for (int i = 1; i < 32; i++) {
      if (sigismember(&pendingSet, i)) {
        printf("1");
      } else {
        printf("0");
      }
    }
    printf("\n");

    j++;
    sleep(1);
    // 10 秒之后
    if (j == 10) {
      // 设置信号集为非阻塞，进程收到信号后，信号会被处理
      sigprocmask(SIG_UNBLOCK, &blockSet, NULL);
    }
  }

  return 0;
}