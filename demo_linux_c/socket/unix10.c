#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
  int fds[2];
  int returnValue;

  // socketpair(2)，创建匿名unix socket
  // SOCK_NONBLOCK非阻塞模式，recv不会阻塞
  returnValue = socketpair(AF_UNIX, SOCK_STREAM | SOCK_NONBLOCK, 0, fds);
  printf("socketpair returnValue=%d\r\n", returnValue);
  printf("errno=%d,%s\r\n", errno, strerror(errno));

  pid_t pid = fork();
  if (pid == 0) {
    close(fds[1]);
    while (1) {
      char msg[128] = {0};
      returnValue = recv(fds[0], msg, sizeof(msg), 0);
      printf("child recv bytes=%d,msg=%s\r\n", returnValue, msg);
      if (returnValue <= 0) {
        printf("parent close\r\n");
        break;
      }
    }
    close(fds[0]);

    return 0;
  }

  close(fds[0]);
  returnValue = write(fds[1], "parent", 6);
  printf("parent send bytes=%d\r\n", returnValue);
  close(fds[1]);

  wait(0);

  return 0;
}