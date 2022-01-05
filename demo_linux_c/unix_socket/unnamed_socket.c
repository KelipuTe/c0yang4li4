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
  int rtvl;

  // socketpair(2)，creates an unnamed pair of connected sockets
  // 创建一对匿名socket，SOCK_NONBLOCK=非阻塞模式，调用recv()时不会阻塞
  rtvl = socketpair(AF_UNIX, SOCK_STREAM | SOCK_NONBLOCK, 0, fds);
  printf("[debug]:socketpair(),rtvl=%d\r\n", rtvl);
  printf("[error]:errno=%d,errstr%s\r\n", errno, strerror(errno));

  pid_t pid = fork();
  if (pid == 0) {
    close(fds[1]);
    
    while (1) {
      char msg[128] = {0};
      rtvl = recv(fds[0], msg, sizeof(msg), 0);
      printf("[debug]:child,recv(),rtvl=%d,msg=%s\r\n", rtvl, msg);
      if (rtvl <= 0) {
        printf("[debug]:child,recv(),rtvl<=0\r\n");
        break;
      }
      sleep(1);
    }

    close(fds[0]);

    return 0;
  }

  close(fds[0]);

  rtvl = write(fds[1], "parent", 6);
  printf("[debug]:parent,write(),rtvl=%d\r\n", rtvl);

  close(fds[1]);

  wait(0);

  return 0;
}