#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
  printf("[debug]:parent,getpid()=%d,getpgrp()=%d,getppid()=%d,getsid(getpid())=%d\r\n",getpid(), getpgrp(), getppid(), getsid(getpid()));

  pid_t pid1 = fork();
  if (pid1 == 0) {
    // 子进程调用了setpgid，它自己是一组
    setpgid(getpid(), getpid());
    printf("[debug]:child1,getpid()=%d,getpgrp()=%d,getppid()=%d,getsid(getpid())=%d\r\n",getpid(), getpgrp(), getppid(), getsid(getpid()));
    
    return 0;
  }

  wait(NULL);

  printf("[debug]:parent,getpid()=%d,getpgrp()=%d,getppid()=%d,getsid(getpid())=%d\r\n",getpid(), getpgrp(), getppid(), getsid(getpid()));

  pid_t pid2 = fork();
  if (pid2 == 0) {
    // 子进程没有调用setpgid，它和父进程一组
    printf("[debug]:child2,getpid()=%d,getpgrp()=%d,getppid()=%d,getsid(getpid())=%d\r\n",getpid(), getpgrp(), getppid(), getsid(getpid()));

    return 0;
  }

  wait(NULL);

  printf("[debug]:parent,getpid()=%d,getpgrp()=%d,getppid()=%d,getsid(getpid())=%d\r\n",getpid(), getpgrp(), getppid(), getsid(getpid()));

  return 0;
}
