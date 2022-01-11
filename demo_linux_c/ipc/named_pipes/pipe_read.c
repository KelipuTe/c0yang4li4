#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

// 命名管道，非父子进程，读取部分
int main() {
  if (access("/tmp/fifo", F_OK)) {
    int rtvl1 = mkfifo("/tmp/fifo", 0666);
    printf("pipe(),rtvl1=%d\r\n", rtvl1);
    printf("errno=%d,%s\r\n", errno, strerror(errno));
  }

  // 一次读取多个字节
  char data[128] = {0};
  int fdRead = open("/tmp/fifo", O_RDONLY);
  while (1) {
    // 清空data
    memset(data, 0, sizeof(data));
    // 读取长度为data数组长度的数据
    int rtvl2 = read(fdRead, data, sizeof(data));
    printf("rtvl2=%d,data=%s\r\n", rtvl2, data);
    if (rtvl2 == 0) {
      printf("write pipe is close\r\n");
      break;
    }
  }
  close(fdRead);

  return 0;
}