#include <arpa/inet.h>
#include <errno.h>
#include <netinet/in.h>
#include <netinet/udp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

// 一次性的 udp 服务端
int main() {
  printf("[debug]:udp server start, getpid()=%d\n", getpid());

  int sockfd = socket(AF_INET, SOCK_DGRAM, 0);

  struct sockaddr_in serverAddr;
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = htons(9501);
  serverAddr.sin_addr.s_addr = inet_addr("0.0.0.0");

  int bindResult = bind(sockfd, (struct sockaddr *)&serverAddr, sizeof(serverAddr));
  printf("[debug]:bindResult=%d\n", bindResult);
  printf("[debug]:errno=%d, error=%s\n", errno, strerror(errno));

  struct sockaddr_in clientAddr;
  socklen_t clientAddrLen = sizeof(clientAddr);
  char msg[1024] = {0};

  ssize_t recvByteNum = recvfrom(sockfd, msg, sizeof(msg), 0, (struct sockaddr *)&clientAddr, &clientAddrLen);
  printf("[debug]:recvByteNum=%ld\n", recvByteNum);
  printf("[debug]:msg=%s, port=%d, ip=%s\n", msg, ntohs(clientAddr.sin_port), inet_ntoa(clientAddr.sin_addr));
  printf("[debug]:errno=%d, error=%s\n", errno, strerror(errno));

  ssize_t sendByteNum = sendto(sockfd, "hello, client", 13, 0, (struct sockaddr *)&clientAddr, sizeof(clientAddr));
  printf("[debug]:sendByteNum=%ld\n", sendByteNum);
  printf("[debug]:errno=%d, error=%s\n", errno, strerror(errno));

  return 0;
}