#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
  printf("[debug]:parent, getpid()=%d\n", getpid());
  pid_t forkResult = fork();

  // 子进程并不会从头开始跑，而是从 fork 这里继续往下执行
  // fork 的返回值，父进程会拿到子进程的pid，子进程会拿到0
  if (forkResult < 0) {
    printf("[error]:fock(), failed\n");
    printf("[error]:errno=%d, strerror=%s\n", errno, strerror(errno));
  } else if (0 == forkResult) {
    printf("[debug]:child, getpid()=%d, forkResult=%d\n", getpid(), forkResult);
  } else {
    sleep(1);
    printf("[debug]:parent, getpid()=%d, forkResult=%d\n", getpid(), forkResult);
  }

  return 0;
}