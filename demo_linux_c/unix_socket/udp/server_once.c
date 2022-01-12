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

  unlink(socketFileNameServer);

  int sockfd = socket(AF_LOCAL, SOCK_DGRAM, 0);
  printf("socket(),sockfd=%d\r\n", sockfd);
  printf("errno=%d,%s\r\n", errno, strerror(errno));

  struct sockaddr_un addressAddr;
  addressAddr.sun_family = AF_UNIX;
  strcpy(addressAddr.sun_path, socketFileNameServer);

  int rtvl1 = bind(sockfd, (struct sockaddr *)&addressAddr, sizeof(addressAddr));
  printf("bind(),rtvl1=%d\r\n", rtvl1);
  printf("errno=%d,%s\r\n", errno, strerror(errno));

  struct sockaddr_un clientAddr;
  socklen_t clientAddrLen = sizeof(clientAddr);
  char msg[1024] = {0};
  ssize_t rtvl2 = recvfrom(sockfd, msg, sizeof(msg), 0, (struct sockaddr *)&clientAddr, &clientAddrLen);
  printf("recvfrom(),rtvl2=%d,msg=%s\r\n", rtvl2, msg);
  printf("errno=%d,%s\r\n", errno, strerror(errno));

  ssize_t rtvl3 = sendto(sockfd, "server", 6, 0, (struct sockaddr *)&clientAddr, sizeof(clientAddr));
  printf("sendto(),rtvl3=%d\r\n", rtvl3);
  printf("errno=%d,%s\r\n", errno, strerror(errno));

  close(sockfd);

  return 0;
}