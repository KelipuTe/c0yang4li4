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
  printf("udp server start,pid=%d\r\n", getpid());

  int sockfd = socket(AF_INET, SOCK_DGRAM, 0);

  struct sockaddr_in serverAddr, clientAddr;
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = htons(9501);
  serverAddr.sin_addr.s_addr = inet_addr("0.0.0.0");

  ssize_t sendBytes = sendto(sockfd, "hello", 5, 0, (struct sockaddr *)&serverAddr, sizeof(serverAddr));
  printf("send bytes=%d\r\n", sendBytes);

  char msg[1024] = {0};
  socklen_t clientAddrLen = sizeof(clientAddr);
  ssize_t recvBytes = recvfrom(sockfd, msg, sizeof(msg), 0, (struct sockaddr *)&clientAddr, &clientAddrLen);
  printf("receive bytes=%d,msg=%s,ip=%s,port=%d\r\n", recvBytes, msg, inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port));

  return 0;
}