#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>

int main() {
  // 查看进程可以打开的文件个数限制
  struct rlimit rlimit1;
  int ret = getrlimit(RLIMIT_NOFILE, &rlimit1);
  printf("open file max num=%d\r\n", rlimit1.rlim_cur);

  // 设置进程可以打开的文件个数限制
  // struct rlimit rlimit2;
  // rlimit2.rlim_max = 1024; //硬限制
  // rlimit2.rlim_cur = 1024; //软限制
  // setrlimit(RLIMIT_NOFILE, &rlimit2);

  return 0;
}