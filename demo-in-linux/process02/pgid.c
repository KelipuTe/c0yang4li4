#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// getpgid 获取进程组 id
int main() {
  printf("[debug]:getpid()=%d, getpgid()=%d, getppid()=%d\n", getpid(), getpgid(getpid()), getppid());

  return 0;
}
