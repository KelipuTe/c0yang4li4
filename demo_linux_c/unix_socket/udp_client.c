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
  char socketFileNameServer[] = "/tmp/unix_udp_server";
  char socketFileNameClient[] = "/tmp/unix_udp_client";

  unlink(socketFileNameClient);

  int sockfd = socket(AF_LOCAL, SOCK_DGRAM, 0);

  struct sockaddr_un addressAddr, clientAddr;
  addressAddr.sun_family = AF_UNIX;
  strcpy(addressAddr.sun_path, socketFileNameServer);

  clientAddr.sun_family = AF_LOCAL;
  strcpy(clientAddr.sun_path, socketFileNameClient);

  int returnValue = bind(sockfd, (struct sockaddr *)&clientAddr, sizeof(clientAddr));
  printf("bind returnValue=%d\r\n", returnValue);
  printf("errno=%d,%s\r\n", errno, strerror(errno));

  char msg[1024] = {0};
  ssize_t sendBytes = sendto(sockfd, "clientAddr", 6, 0, (struct sockaddr *)&addressAddr, sizeof(addressAddr));
  printf("send bytes=%d\r\n", sendBytes);

  socklen_t addressAddrLen = sizeof(addressAddr);
  ssize_t recvValue = recvfrom(sockfd, msg, sizeof(msg), 0, (struct sockaddr *)&addressAddr, &addressAddrLen);
  printf("recv bytes=%d,msg=%s\r\n", recvValue, msg);

  close(sockfd);
}