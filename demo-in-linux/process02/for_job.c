#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

// 用于查看前台进程（组）和后台进程（组）
int main() {
  printf("[debug]:getpid()=%d\n", getpid());
  while (1) {
    sleep(5);
    printf("[debug]:getpid()=%d\n", getpid());
  }
  return 0;
}