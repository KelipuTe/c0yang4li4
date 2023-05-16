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
  printf("[debug]:unix udp client start, getpid()=%d\n", getpid());

  char socketFileNameServer[] = "/tmp/unix_udp_server";
  char socketFileNameClient[] = "/tmp/unix_udp_client";

  unlink(socketFileNameClient);

  int sockfd = socket(AF_LOCAL, SOCK_DGRAM, 0);
  printf("[debug]:sockfd=%d\n", sockfd);
  printf("[debug]:errno=%d, error=%s\n", errno, strerror(errno));

  struct sockaddr_un addressAddr;
  addressAddr.sun_family = AF_UNIX;
  strcpy(addressAddr.sun_path, socketFileNameServer);

  struct sockaddr_un clientAddr;
  clientAddr.sun_family = AF_LOCAL;
  strcpy(clientAddr.sun_path, socketFileNameClient);

  int bindResult = bind(sockfd, (struct sockaddr *)&clientAddr, sizeof(clientAddr));
  printf("[debug]:bindResult=%d\n", bindResult);
  printf("[debug]:errno=%d, error=%s\n", errno, strerror(errno));

  char msg[1024] = {0};
  ssize_t sendByteNum = sendto(sockfd, "clientAddr", 6, 0, (struct sockaddr *)&addressAddr, sizeof(addressAddr));
  printf("[debug]:sendByteNum=%ld\n", sendByteNum);
  printf("[debug]:errno=%d, error=%s\n", errno, strerror(errno));

  socklen_t addressAddrLen = sizeof(addressAddr);
  ssize_t recvByteNum = recvfrom(sockfd, msg, sizeof(msg), 0, (struct sockaddr *)&addressAddr, &addressAddrLen);
  printf("[debug]:recvByteNum=%ld, msg=%s\n", recvByteNum, msg);
  printf("[debug]:errno=%d, error=%s\n", errno, strerror(errno));

  close(sockfd);
}