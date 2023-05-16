#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
  printf("[debug]:unix udp server start, getpid()=%d\n", getpid());

  char socketFileNameServer[] = "/tmp/unix_udp_server";

  unlink(socketFileNameServer);

  int sockfd = socket(AF_LOCAL, SOCK_DGRAM, 0);
  printf("[debug]:sockfd=%d\n", sockfd);
  printf("[debug]:errno=%d, error=%s\n", errno, strerror(errno));

  struct sockaddr_un addressAddr;
  addressAddr.sun_family = AF_UNIX;
  strcpy(addressAddr.sun_path, socketFileNameServer);

  int bindResult = bind(sockfd, (struct sockaddr *)&addressAddr, sizeof(addressAddr));
  printf("[debug]:bindResult=%d\n", bindResult);
  printf("[debug]:errno=%d, error=%s\n", errno, strerror(errno));

  struct sockaddr_un clientAddr;
  socklen_t clientAddrLen = sizeof(clientAddr);
  char msg[1024] = {0};
  ssize_t recvByteNum = recvfrom(sockfd, msg, sizeof(msg), 0, (struct sockaddr *)&clientAddr, &clientAddrLen);
  printf("[debug]:recvByteNum=%ld, msg=%s\n", recvByteNum, msg);
  printf("[debug]:errno=%d, error=%s\n", errno, strerror(errno));

  ssize_t sendByteNum = sendto(sockfd, "server", 6, 0, (struct sockaddr *)&clientAddr, sizeof(clientAddr));
  printf("[debug]:sendByteNum=%ld\n", sendByteNum);
  printf("[debug]:errno=%d, error=%s\n", errno, strerror(errno));

  close(sockfd);

  return 0;
}