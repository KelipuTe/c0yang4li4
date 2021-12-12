#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
  umask(0);

  pid_t pid;

  pid = fork();
  if (pid > 0) { //父进程退出
    return 0;
  }

  if (setsid() == -1) { //调用setsid，返回-1表示失败了
    return 0;
  }

  pid = fork();
  if (pid > 0) { //让会话首进程退出
    return 0;
  }

  chdir("/"); //修改进程的工作目录

  //关闭0、1、2这些文件描述符
  struct rlimit rlim;
  int ret = getrlimit(RLIMIT_NOFILE, &rlim);
  for (int i = 0; i < rlim.rlim_max; i++) {
    close(i);
  }

  // dup函数可以复制一个文件描述符，然后返回一个新的文件描述符
  // 返回的文件描述符是当前最大的文件描述符+1
  int fd0 = open("/dev/null", O_RDWR);    //这里打开的文件描述符返回是0
  int fd1 = dup(0);                       //复制文件描述符0，返回的文件描述符是1
  int fd2 = dup(0);                       //复制文件描述符0，返回的文件描述符是2
  if (fd0 != 0 && fd1 != 1 && fd2 != 2) { //判断文件描述符打开情况
    return 0;
  }

  pid = fork();
  if (pid == 0) {
    while (1) {
      printf("child,pid=%d\r\n", getpid());
      sleep(2);
    }

    return 0;
  }

  while (1) {
    printf("parent,pid=%d\r\n", getpid());
    sleep(2);
  }

  return 0;
}