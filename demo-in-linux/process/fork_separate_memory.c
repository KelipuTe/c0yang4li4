#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

int ga = 300;

// fock 父子进程内存隔离
int main() {
  printf("[debug]:parent, getpid()=%d\n", getpid());
  pid_t forkResult = fork();

  int pa = 400;
  if (forkResult < 0) {
    printf("[error]:fock(), failed\n");
    printf("[error]:errno=%d, strerror=%s\n", errno, strerror(errno));
  } else if (0 == forkResult) {
    printf("[debug]:child, getpid()=%d, ga=%d, pa=%d\n", getpid(), ga, pa);
    // 这里的修改不会影响父进程
    ga = 302;
    pa = 402;
    printf("[debug]:child, getpid()=%d, ga=%d, pa=%d\n", getpid(), ga, pa);
  } else {
    sleep(1);
    printf("[debug]:parent, getpid()=%d, ga=%d, pa=%d\n", getpid(), ga, pa);
    // 这里的修改不会影响子进程
    ga = 301;
    pa = 401;
    printf("[debug]:parent, getpid()=%d, ga=%d, pa=%d\n", getpid(), ga, pa);
  }

  return 0;
}