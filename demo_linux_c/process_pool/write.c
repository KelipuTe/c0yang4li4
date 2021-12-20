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

int main() {
  char pool_pipe_path[] = "/tmp/process_pool/pool_fifo";
  int temp_retval;

  if (access(pool_pipe_path, F_OK)) {
    temp_retval = mkfifo(pool_pipe_path, 0666);
    if (0 != temp_retval) {
      printf("parent,mkfifo fail\r\n");
      printf("errno=%d,strerror=%s\r\n", errno, strerror(errno));
      return 0;
    }
  }

  int pool_pipe_fd = open(pool_pipe_path, O_WRONLY);
  char msg[128] = {0};
  while (1) {
    fgets(msg, sizeof(msg), stdin);
    if (0 == strncasecmp("exit", msg, 4)) {
      break;
    }
    write(pool_pipe_fd, msg, strlen(msg));
    memset(msg, 0, sizeof(msg));
  }

  close(pool_pipe_fd);

  return 0;
}
