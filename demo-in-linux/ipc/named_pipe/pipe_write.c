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
  printf("[debug]:getpid()=%d\n", getpid());
  if (access("/tmp/fifo", F_OK)) {
    int mkfifoResult = mkfifo("/tmp/fifo", 0666);
    printf("[debug]:mkfifoResult=%d, errno=%d, error=%s\n", mkfifoResult, errno, strerror(errno));
  }

  int fdWrite = open("/tmp/fifo", O_WRONLY);
  int writeByteNum = write(fdWrite, "hello", 5);
  printf("[debug]:writeByteNum=%d\n", writeByteNum);
  close(fdWrite);

  return 0;
}