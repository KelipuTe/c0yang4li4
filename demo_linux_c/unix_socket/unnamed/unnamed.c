#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>
#include <sys/wait.h>
#include <unistd.h>

// 匿名unix socket
int main() {
  int fds[2];

  // socketpair(2)
  // #include <sys/socket.h>
  // 创建一对匿名socket
  // __domain参数，AF_UNIX表示使用unix socket
  int rtvl1 = socketpair(AF_UNIX, SOCK_STREAM | SOCK_NONBLOCK, 0, fds);
  printf("socketpair(),rtvl1=%d\r\n", rtvl1);
  printf("errno=%d,errstr%s\r\n", errno, strerror(errno));

  pid_t pid = fork();
  if (pid == 0) {
    close(fds[1]);

    while (1) {
      char msg[128] = {0};
      int rtvl2 = recv(fds[0], msg, sizeof(msg), 0);
      printf("child,recv(),rtvl2=%d,msg=%s\r\n", rtvl2, msg);
      printf("errno=%d,errstr%s\r\n", errno, strerror(errno));
      if (rtvl2 <= 0) {
        printf("child,recv(),rtvl2<=0\r\n");
        break;
      }
      sleep(1);
    }

    close(fds[0]);

    return 0;
  }

  close(fds[0]);

  int rtvl3 = write(fds[1], "parent", 6);
  printf("parent,write(),rtvl3=%d\r\n", rtvl3);
  printf("errno=%d,errstr%s\r\n", errno, strerror(errno));

  close(fds[1]);

  wait(0);

  return 0;
}