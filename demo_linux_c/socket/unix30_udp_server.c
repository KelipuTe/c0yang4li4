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

  struct sockaddr_un addressAddr, clientAddr;
  addressAddr.sun_family = AF_UNIX;
  strcpy(addressAddr.sun_path, socketFileNameServer);

  int returnValue = bind(sockfd, (struct sockaddr *)&addressAddr, sizeof(addressAddr));
  printf("bind returnValue=%d\r\n", returnValue);
  printf("errno=%d,%s\r\n", errno, strerror(errno));

  char msg[1024] = {0};
  socklen_t clientAddrLen = sizeof(clientAddr);
  ssize_t recvValue = recvfrom(sockfd, msg, sizeof(msg), 0, (struct sockaddr *)&clientAddr, &clientAddrLen);
  printf("recv bytes=%d,msg=%s\r\n", recvValue, msg);

  ssize_t sendBytes = sendto(sockfd, "server", 6, 0, (struct sockaddr *)&clientAddr, sizeof(clientAddr));
  printf("send bytes=%d\r\n", sendBytes);

  close(sockfd);

  return 0;
}