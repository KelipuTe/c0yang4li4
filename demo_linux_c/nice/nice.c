#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <sys/time.h>
#include <unistd.h>

int main() {
  pid_t pid = fork();
  // getpriority(2)、setpriority(2)
  // get/set program scheduling priority，获取、设置进程nice值
  // 当两个进程优先级不同的时候，就可以手动调整
  if (pid == 0) {
    int rtvl1 = setpriority(PRIO_PROCESS, getpid(), -10);
    printf("child,setpriority()=%d\r\n", rtvl1);
    int rtvl2 = getpriority(PRIO_PROCESS, getpid());
    printf("child,getpriority()=%d\r\n", rtvl2);
    while (1) {
      sleep(1);
      printf("child,getpid()=%d\r\n", getpid());
    }

    return 0;
  }

  int rtvl1 = setpriority(PRIO_PROCESS, getpid(), 10);
  printf("parent,setpriority()=%d\r\n", rtvl1);
  int rtvl2 = getpriority(PRIO_PROCESS, getpid());
  printf("parent,getpriority()=%d\r\n", rtvl2);
  while (1) {
    sleep(5);
    printf("parent,getpid()=%d\r\n", getpid());
  }

  return 0;
}
