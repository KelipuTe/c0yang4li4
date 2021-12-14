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
  if (access("./fifo", F_OK)) {
    int result = mkfifo("./fifo", 0666);
    printf("errno=%d,%s\r\n", errno, strerror(errno));
  }

  // 一次读取多个字节
  char data[128] = {0};
  int fdRead = open("./fifo", O_RDONLY);
  while (1) {
    // 清空data
    memset(data, 0, sizeof(data));
    int bytes = read(fdRead, data, sizeof(data));
    printf("read %d bytes,data=%s\r\n", bytes, data);
    if (bytes == 0) {
      printf("write pipe is close\r\n");
      break;
    }
  }
  close(fdRead);

  return 0;
}