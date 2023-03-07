#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

// 用于构造僵尸进程
int main() {
  printf("[debug]:parent, getpid()=%d\n", getpid());
  pid_t forkResult = fork();

  if (forkResult < 0) {
    printf("[error]:fock(), failed\n");
    printf("[error]:errno=%d, strerror=%s\n", errno, strerror(errno));
  } else if (0 == forkResult) {
    // 僵尸进程
    printf("[debug]:child, getpid()=%d, forkResult=%d\n", getpid(), forkResult);
  } else {
    while (1) {
      printf("[debug]:parent, getpid()=%d, forkResult=%d\n", getpid(), forkResult);
      sleep(10);
    }
  }

  return 0;
}