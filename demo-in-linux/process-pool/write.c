#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

// 通过命名管道向进程池的父进程发送数据

int main() {
  char poolPipePath[] = "/tmp/process_pool_fifo";
  int mkfifoResult;

  if (access(poolPipePath, F_OK)) {
    mkfifoResult = mkfifo(poolPipePath, 0666);
    if (0 != mkfifoResult) {
      printf("[debug]:parent, mkfifo() fail\n");
      printf("[debug]:errno=%d, strerror=%s\n", errno, strerror(errno));
      return 0;
    }
  }

  int poolPipeFD = open(poolPipePath, O_WRONLY);
  char msg[128] = {0};
  while (1) {
    fgets(msg, sizeof(msg), stdin);
    if (0 == strncasecmp("exit", msg, 4)) {
      break;
    }
    write(poolPipeFD, msg, strlen(msg));
    memset(msg, 0, sizeof(msg));
  }

  close(poolPipeFD);

  return 0;
}
