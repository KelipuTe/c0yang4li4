#include <stdio.h>
#include <unistd.h>

// 用于查看进程内存
int main() {
  printf("[debug]:getpid()=%d\n", getpid());
  while (1) {
    sleep(10);
  }
  return 0;
}