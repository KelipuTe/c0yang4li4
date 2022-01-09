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
  // 父进程退出
  if (pid > 0) {
    return 0;
  }

  // 调用setsid()，变成会话首进程
  int rtvl1 = setsid();
  if (-1 == rtvl1) {
    // 返回-1表示失败了
    return 0;
  }

  pid = fork();
  // 会话首进程退出
  if (pid > 0) {
    return 0;
  }

  // 修改进程的工作目录
  chdir("/");

  // 关闭0、1、2这些文件描述符
  struct rlimit rlim;
  int rtvl2 = getrlimit(RLIMIT_NOFILE, &rlim);
  for (int i = 0; i < rlim.rlim_max; i++) {
    close(i);
  }

  // dup()函数可以复制一个文件描述符，然后返回一个新的文件描述符
  // 返回的文件描述符是当前最大的文件描述符+1

  // 这里打开的文件描述符返回是0
  int fd0 = open("/dev/null", O_RDWR);
  // 复制文件描述符0，返回的文件描述符是1
  int fd1 = dup(0);
  //复制文件描述符0，返回的文件描述符是2
  int fd2 = dup(0);
  //判断文件描述符打开情况
  if (fd0 != 0 && fd1 != 1 && fd2 != 2) {
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