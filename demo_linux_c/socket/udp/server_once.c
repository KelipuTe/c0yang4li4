#include <arpa/inet.h>
#include <errno.h>
#include <netinet/in.h>
#include <netinet/udp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

// 一次性的udp服务端
int main() {
  printf("udp server start,getpid()=%d\r\n", getpid());

  // __type参数，SOCK_DGRAM表示tcp
  int sockfd = socket(AF_INET, SOCK_DGRAM, 0);

  struct sockaddr_in serverAddr;
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = htons(9501);
  serverAddr.sin_addr.s_addr = inet_addr("0.0.0.0");

  int rtvl1 = bind(sockfd, (struct sockaddr *)&serverAddr, sizeof(serverAddr));
  printf("bind(),rtvl1=%d\r\n", rtvl1);
  printf("errno=%d,%s\r\n", errno, strerror(errno));

  struct sockaddr_in clientAddr;
  socklen_t clientAddrLen = sizeof(clientAddr);
  char msg[1024] = {0};

  // recvfrom(2)
  // #include <sys/socket.h>
  // 从socket读取数据
  ssize_t rtvl2 = recvfrom(sockfd, msg, sizeof(msg), 0, (struct sockaddr *)&clientAddr, &clientAddrLen);

  // inet_ntoa(3)
  // #include <sys/socket.h>
  // #include <netinet/in.h>
  // #include <arpa/inet.h>
  // 网络字节序转点分10进制
  // ntohs(3)
  // #include <arpa/inet.h>
  // 网络字节序转主机字节序
  printf("recvfrom(),rtvl2=%d\r\n", rtvl2);
  printf("msg=%s,ip=%s,port=%d\r\n", msg, inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port));
  printf("errno=%d,%s\r\n", errno, strerror(errno));

  // sendto(2)
  // #include <sys/socket.h>
  // 向socket发送数据
  ssize_t rtvl3 = sendto(sockfd, "hello, client", 13, 0, (struct sockaddr *)&clientAddr, sizeof(clientAddr));
  printf("sendto(),rtvl3=%d\r\n", rtvl3);
  printf("errno=%d,%s\r\n", errno, strerror(errno));

  return 0;
}