#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

// pid 进程标识、ppid 父进程标识
int main() {
  printf("[debug]:parent, getpid()=%d\n", getpid());
  pid_t forkResult = fork();

  if (forkResult < 0) {
    printf("[error]:fock(), failed\n");
    printf("[error]:errno=%d, strerror=%s\n", errno, strerror(errno));
  } else if (0 == forkResult) {
    printf("[debug]:child, getpid()=%d, getppid=%d\n", getpid(), getppid());
  } else {
    // 这里不 sleep，子进程打印出来的 ppid 就有可能会变成 1
    sleep(1);
    printf("[debug]:parent, getpid()=%d, getppid=%d\n", getpid(), getppid());
  }

  return 0;
}