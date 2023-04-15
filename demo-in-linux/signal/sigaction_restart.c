#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void signal_handler(int signo) {
  printf("[info]:signal_no=%d\n", signo);
}

int main() {
  printf("[debug]:getpid()=%d\n", getpid());

  // 收到终端信号时，read() 会重启，不会输出错误
  struct sigaction action;
  action.sa_handler = signal_handler;
  action.sa_flags = SA_RESTART;

  // 修改收到 SIGINT 时的逻辑
  if (sigaction(SIGINT, &action, NULL)) {
    printf("[debug]:sigaction() fail\n");
  }

  char buffer[128] = {0};
  int byte = read(0, buffer, sizeof(buffer));
  printf("[debug]:byte=%d,errno=%d,error=%s\n", byte, errno, strerror(errno));

  return 0;
}