#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void signal_handler(int signo) {
  printf("[info]:signal_no=%d\n", signo);
  // 处理 SIGALRM 的时候，再调用 alarm()，就可以实现类似定时任务的结构
  alarm(2);
}

int main() {
  printf("[debug]:getpid()=%d\n", getpid());
  signal(SIGALRM, signal_handler);
  // 2 秒之后，触发 SIGALRM 信号
  alarm(2);

  char buffer[128] = {0};
  while (1) {
    int byte = read(0, buffer, sizeof(buffer));
    printf("[debug]:byte=%d,errno=%d,error=%s\n", byte, errno, strerror(errno));
  }

  return 0;
}