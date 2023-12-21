#include <stdio.h>
#include <unistd.h>

// 用于查看进程的内存资源
int main() {
  printf("[debug]:getpid()=%d\n", getpid());
  while (1) {
    sleep(2);
  }
  return 0;
}