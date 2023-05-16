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
  printf("[debug]:unix tcp server start, getpid()=%d\n", getpid());

  // unix socket，socket文件名
  char sockerFileName[] = "/tmp/unix_tcp";

  unlink(sockerFileName);

  int sockfd = socket(AF_LOCAL, SOCK_STREAM, 0);
  printf("[debug]:sockfd=%d\n", sockfd);
  printf("[debug]:errno=%d, error=%s\n", errno, strerror(errno));

  struct sockaddr_un addressAddr;
  addressAddr.sun_family = AF_UNIX;
  strcpy(addressAddr.sun_path, sockerFileName);

  int bindResult = bind(sockfd, (struct sockaddr *)&addressAddr, sizeof(addressAddr));
  printf("[debug]:bindResult=%d\n", bindResult);
  printf("[debug]:errno=%d, error=%s\n", errno, strerror(errno));

  int listenResult = listen(sockfd, 128);
  printf("[debug]:listenResult=%d\n", listenResult);
  printf("[debug]:errno=%d, error=%s\n", errno, strerror(errno));

  struct sockaddr_un clientAddr;
  socklen_t clientAddrLen = sizeof(clientAddr);
  int connfd = accept(sockfd, (struct sockaddr *)&clientAddr, &clientAddrLen);
  printf("[debug]:connfd=%d\n", sockfd);
  printf("[debug]:errno=%d, error=%s\n", errno, strerror(errno));

  char msg[1024] = {0};
  ssize_t recvByteNum = recv(connfd, msg, sizeof(msg), 0);
  printf("[debug]:recvByteNum=%ld, msg=%s\n", recvByteNum, msg);
  printf("[debug]:errno=%d, error=%s\n", errno, strerror(errno));

  ssize_t sendByteNum = send(connfd, "server", 6, 0);
  printf("[debug]:sendByteNum=%ld\n", sendByteNum);
  printf("[debug]:errno=%d, error=%s\n", errno, strerror(errno));

  close(connfd);
  close(sockfd);

  return 0;
}