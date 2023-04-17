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
  printf("[debug]:getpid()=%d\n", getpid());
  if (access("/tmp/fifo", F_OK)) {
    int mkfifoResult = mkfifo("/tmp/fifo", 0666);
    printf("[debug]:mkfifoResult=%d, errno=%d, error=%s\n", mkfifoResult, errno, strerror(errno));
  }

  // 一次读取多个字节
  char data[128] = {0};
  int fdRead = open("/tmp/fifo", O_RDONLY);
  while (1) {
    // 清空data
    memset(data, 0, sizeof(data));
    // 读取长度为 data 数组长度的数据
    int readByteNum = read(fdRead, data, sizeof(data));
    printf("[debug]:readByteNum=%d, data=%s\n", readByteNum, data);
    if (readByteNum == 0) {
      printf("[debug]:write pipe is close\n");
      break;
    }
  }
  close(fdRead);

  return 0;
}