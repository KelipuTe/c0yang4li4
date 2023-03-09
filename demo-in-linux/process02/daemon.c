#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
  pid_t forkResult;

  // 创建子进程
  forkResult = fork();
  // 父进程退出
  if (forkResult > 0) {
    return 0;
  }

  // 子进程调用 setsid()，变成会话首进程
  int setsidResult = setsid();
  if (-1 == setsidResult) {
    // 返回 -1 表示失败了
    return 0;
  }

  // 创建子进程
  forkResult = fork();
  // 会话首进程退出
  if (forkResult > 0) {
    return 0;
  }

  // 修改子进程的工作目录
  chdir("/");
  // 重设文件权限掩码
  umask(0);

  // 关闭不必要的文件描述符
  struct rlimit t4rlimit;
  int getrlimitResult = getrlimit(RLIMIT_NOFILE, &t4rlimit);
  for (int i = 0; i < t4rlimit.rlim_max; i++) {
    close(i);
  }

  // dup() 可以复制一个文件描述符，然后返回一个新的文件描述符
  // 返回的文件描述符是当前最大的文件描述符 +1

  // 打开黑洞文件，这里打开的文件描述符返回是 0
  int fd0 = open("/dev/null", O_RDWR);
  // 复制文件描述符 0，返回的文件描述符是 1
  int fd1 = dup(0);
  // 复制文件描述符 0，返回的文件描述符是 2
  int fd2 = dup(0);
  // 判断文件描述符打开情况
  if (0 != fd0 && 1 != fd1 && 2 != fd2) {
    return 0;
  }

  forkResult = fork();
  if (0 == forkResult) {
    while (1) {
      printf("[debug]:daemon child, getpid()=%d\n", getpid());
      sleep(2);
    }

    return 0;
  }

  while (1) {
    printf("[debug]:daemon parent, getpid()=%d\n", getpid());
    sleep(2);
  }

  return 0;
}