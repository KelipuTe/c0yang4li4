#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

int ga = 300;

// vfock 父子进程共享内存
int main() {
  printf("[debug]:parent, getpid()=%d\n", getpid());
  pid_t vforkResult = vfork();

  int pa = 400;
  if (vforkResult < 0) {
    printf("[error]:vfork(), failed\n");
    printf("[error]:errno=%d, strerror=%s\n", errno, strerror(errno));
  } else if (0 == vforkResult) {
    printf("[debug]:child, getpid()=%d, ga=%d, pa=%d\n", getpid(), ga, pa);
    // 这里的修改会影响父进程
    ga = 302;
    pa = 402;
    printf("[debug]:child, getpid()=%d, ga=%d, pa=%d\n", getpid(), ga, pa);
  } else {
    printf("[debug]:parent, getpid()=%d, ga=%d, pa=%d\n", getpid(), ga, pa);
  }

  return 0;
}