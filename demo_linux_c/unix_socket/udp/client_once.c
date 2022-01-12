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
  printf("socket(),sockfd=%d\r\n", sockfd);
  printf("errno=%d,%s\r\n", errno, strerror(errno));

  struct sockaddr_un addressAddr;
  addressAddr.sun_family = AF_UNIX;
  strcpy(addressAddr.sun_path, socketFileNameServer);

  struct sockaddr_un clientAddr;
  clientAddr.sun_family = AF_LOCAL;
  strcpy(clientAddr.sun_path, socketFileNameClient);

  int rtvl1 = bind(sockfd, (struct sockaddr *)&clientAddr, sizeof(clientAddr));
  printf("bind(),rtvl1=%d\r\n", rtvl1);
  printf("errno=%d,%s\r\n", errno, strerror(errno));

  char msg[1024] = {0};
  ssize_t rtvl2 = sendto(sockfd, "clientAddr", 6, 0, (struct sockaddr *)&addressAddr, sizeof(addressAddr));
  printf("sendto(),rtvl2=%d\r\n", rtvl2);

  socklen_t addressAddrLen = sizeof(addressAddr);
  ssize_t rtvl3 = recvfrom(sockfd, msg, sizeof(msg), 0, (struct sockaddr *)&addressAddr, &addressAddrLen);
  printf("recvfrom(),rtvl3=%d,msg=%s\r\n", rtvl3, msg);

  close(sockfd);
}