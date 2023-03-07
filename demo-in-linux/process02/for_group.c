#include <stdio.h>
#include <unistd.h>

// 用于 pstree 查看进程组
int main() {
  printf("[debug]:getpid()=%d, getpgid()=%d, getppid()=%d\n", getpid(), getpgid(getpid()), getppid());
  while (1) {
    sleep(10);
  }

  return 0;
}