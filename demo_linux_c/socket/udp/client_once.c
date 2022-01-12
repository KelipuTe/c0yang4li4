#include <arpa/inet.h>
#include <errno.h>
#include <netinet/in.h>
#include <netinet/udp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

int main() {
  printf("udp server start,getpid()=%d\r\n", getpid());

  int sockfd = socket(AF_INET, SOCK_DGRAM, 0);

  struct sockaddr_in serverAddr;
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = htons(9501);
  serverAddr.sin_addr.s_addr = inet_addr("0.0.0.0");

  ssize_t rtvl1 = sendto(sockfd, "hello, server", 13, 0, (struct sockaddr *)&serverAddr, sizeof(serverAddr));
  printf("sendto(),rtvl1=%d\r\n", rtvl1);
  printf("errno=%d,%s\r\n", errno, strerror(errno));

  struct sockaddr_in clientAddr;
  socklen_t clientAddrLen = sizeof(clientAddr);
  char msg[1024] = {0};
  ssize_t rtvl2 = recvfrom(sockfd, msg, sizeof(msg), 0, (struct sockaddr *)&clientAddr, &clientAddrLen);
  printf("recvfrom(),rtvl2=%d\r\n", rtvl2);
  printf("msg=%s,ip=%s,port=%d\r\n", msg, inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port));
  printf("errno=%d,%s\r\n", errno, strerror(errno));

  return 0;
}