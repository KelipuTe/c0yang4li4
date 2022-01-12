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
  // unix socket，socket文件名
  char sockerFileName[] = "/tmp/unix_tcp";

  unlink(sockerFileName);

  // socket(2)
  // __family参数，AF_LOCAL=unix socket
  int sockfd = socket(AF_LOCAL, SOCK_STREAM, 0);
  printf("socket(),sockfd=%d\r\n", sockfd);
  printf("errno=%d,%s\r\n", errno, strerror(errno));

  // unix(7)
  // unix socket地址
  struct sockaddr_un addressAddr;
  addressAddr.sun_family = AF_UNIX;
  strcpy(addressAddr.sun_path, sockerFileName);

  int rtvl1 = bind(sockfd, (struct sockaddr *)&addressAddr, sizeof(addressAddr));
  printf("bind(),rtvl1=%d\r\n", rtvl1);
  printf("errno=%d,%s\r\n", errno, strerror(errno));

  int rtvl2 = listen(sockfd, 128);
  printf("listen(),rtvl2=%d\r\n", rtvl2);
  printf("errno=%d,%s\r\n", errno, strerror(errno));

  struct sockaddr_un clientAddr;
  socklen_t clientAddrLen = sizeof(clientAddr);
  int connfd = accept(sockfd, (struct sockaddr *)&clientAddr, &clientAddrLen);
  printf("accept(),connfd=%d\r\n", connfd);
  printf("errno=%d,%s\r\n", errno, strerror(errno));

  char msg[1024] = {0};
  ssize_t rtvl3 = recv(connfd, msg, sizeof(msg), 0);
  printf("recv(),rtvl3=%d,msg=%s\r\n", rtvl3, msg);
  printf("errno=%d,%s\r\n", errno, strerror(errno));

  ssize_t rtvl4 = send(connfd, "server", 6, 0);
  printf("send(),rtvl4=%d\r\n", rtvl4);
  printf("errno=%d,%s\r\n", errno, strerror(errno));

  close(connfd);
  close(sockfd);

  return 0;
}