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

  int sockfd = socket(AF_LOCAL, SOCK_STREAM, 0);

  // unix(7)，unix socket地址
  struct sockaddr_un addressAddr, clientAddr;
  addressAddr.sun_family = AF_UNIX;
  strcpy(addressAddr.sun_path, sockerFileName);

  int returnValue;

  returnValue = bind(sockfd, (struct sockaddr *)&addressAddr, sizeof(addressAddr));
  printf("bind returnValue=%d\r\n", returnValue);
  printf("errno=%d,%s\r\n", errno, strerror(errno));

  returnValue = listen(sockfd, 128);
  printf("listen returnValue=%d\r\n", returnValue);
  printf("errno=%d,%s\r\n", errno, strerror(errno));

  socklen_t clientAddrLen = sizeof(clientAddr);
  int connfd = accept(sockfd, (struct sockaddr *)&clientAddr, &clientAddrLen);
  printf("connfd=%d\r\n", connfd);
  printf("errno=%d,%s\r\n", errno, strerror(errno));

  char msg[1024] = {0};
  ssize_t recvValue = recv(connfd, msg, sizeof(msg), 0);
  printf("server recv bytes=%d,msg=%s\r\n", recvValue, msg);

  ssize_t sendValue = send(connfd, "server", 6, 0);
  printf("server send bytes=%d\r\n", sendValue);

  close(connfd);
  close(sockfd);

  return 0;
}