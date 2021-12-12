#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <sys/time.h>
#include <unistd.h>

int main() {
  pid_t pid = fork();

  // setpriority用于设置进程nice值
  // getpriority可以获取进程nice值
  // 当两个进程优先级不同的时候就可以手动调整
  if (pid == 0) {
    int ret = setpriority(PRIO_PROCESS, getpid(), -10);
    int n = getpriority(PRIO_PROCESS, getpid());
    printf("child,nice=%d\r\n", n);
    while (1) {
      sleep(1);
      printf("child,pid=%d\r\n", getpid());
    }

    return 0;
  }

  int ret = setpriority(PRIO_PROCESS, getpid(), 10);
  int n = getpriority(PRIO_PROCESS, getpid());
  printf("parent,nice=%d\r\n", n);
  while (1) {
    sleep(5);
    printf("parent,pid=%d\r\n", getpid());
  }

  return 0;
}
