#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

// 命名管道，父子进程
int main() {
  // 判断fifo文件是否存在，不存在就创建
  // access(2)
  // #include <unistd.h>
  // access()用于检查用户是否有某个文件的权限，也可以变相用于检查文件存不存在
  if (access("/tmp/fifo", F_OK)) {
    // mkfifo(1)、mkfifo(3)
    // #include <sys/types.h>
    // #include <sys/stat.h>
    int rtvl1 = mkfifo("/tmp/fifo", 0666);
    printf("mkfifo(),rtvl1=%d\r\n", rtvl1);
    printf("errno=%d,%s\r\n", errno, strerror(errno));
  }

  pid_t pid = fork();
  if (pid == 0) {
    // 子进程读取父进程的数据
    // open(2)
    // #include <fcntl.h>
    // 打开fifo文件，读取数据
    int fdRead = open("/tmp/fifo", O_RDONLY);
    printf("open(),fdRead=%d\r\n", fdRead);

    int rtvl2 = 1;
    char data;
    while (rtvl2 > 0) {
      rtvl2 = read(fdRead, &data, 1);
      if (rtvl2 > 0) {
        printf("rtvl2=%d,data=%c\r\n", rtvl2, data);
      } else {
        printf("\r\n");
        break;
      }
    }
    close(fdRead);

    return 0;
  }
  // 父进程给子进程发送数据
  // 打开fifo文件，写入数据
  int fdWrite = open("/tmp/fifo", O_WRONLY);
  write(fdWrite, "hello", 5);
  // 当这里关闭时，子进程还在读的话，就会返回0，表示父进程已经关闭了
  close(fdWrite);

  wait(0);

  return 0;
}