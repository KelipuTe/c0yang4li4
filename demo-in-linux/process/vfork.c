#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

// vfock 创建子进程
int main() {
  printf("[debug]:parent, getpid()=%d\n", getpid());
  pid_t vforkResult = vfork();

  // vfork 的返回值和 fork 一样
  if (vforkResult < 0) {
    printf("[error]:vfork(), failed\n");
    printf("[error]:errno=%d, strerror=%s\n", errno, strerror(errno));
  } else if (0 == vforkResult) {
    printf("[debug]:child, getpid()=%d, vforkResult=%d\n", getpid(), vforkResult);
  } else {
    printf("[debug]:parent, getpid()=%d, vforkResult=%d\n", getpid(), vforkResult);
  }

  return 0;
}