#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>

int main() {
  // 查看
  struct rlimit t4rlimit;
  int getrlimitResult = getrlimit(RLIMIT_NOFILE, &t4rlimit);
  printf("[debug]:open file, cur num=%ld, max num=%ld\n", t4rlimit.rlim_cur,t4rlimit.rlim_max);

  // 设置
  // struct rlimit t4rlimit;
  // t4rlimit.rlim_max = 1024; // 硬限制
  // t4rlimit.rlim_cur = 1024; // 软限制
  // setrlimit(RLIMIT_NOFILE, &t4rlimit);

  return 0;
}