#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void signal_handler(int signo) {
  printf("signo=%d\r\n", signo);
}

int main() {
  printf("pid=%d\r\n", getpid());

  struct sigaction act;
  act.sa_handler = signal_handler;
  sigemptyset(&act.sa_mask);
  // 收到终端信号时，下面会输出错误
  act.sa_flags = 0;
  // 收到终端信号时，read函数直接重启，不会输出错误
  // act.sa_flags = SA_RESTART;

  if (sigaction(SIGINT, &act, NULL)) {
    printf("sigaction fail\r\n");
  }

  char buffer[128] = {0};
  while (1) {
    int byte = read(0, buffer, sizeof(buffer));
    printf("byte=%d,errno=%d,error=%s\r\n", byte, errno, strerror(errno));
  }

  return 0;
}