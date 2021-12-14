#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

// 命名管道，非父子进程，写入部分
int main() {
  if (access("./fifo", F_OK)) {
    int result = mkfifo("./fifo", 0666);
    printf("errno=%d,%s\r\n", errno, strerror(errno));
  }

  int fdWrite = open("./fifo", O_WRONLY);
  write(fdWrite, "hello", 5);
  close(fdWrite);

  return 0;
}