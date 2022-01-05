#include <errno.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>

// 一次性的htcp服务端
int main() {
  printf("tcp server start,pid=%d\r\n", getpid());

  // socket(2)，创建socket
  // socket初始化，AF_INET=ipv4，SOCK_STREAM=tcp，0=tcp
  int sockfd = socket(AF_INET, SOCK_STREAM, 0);
  printf("errno=%d,%s\r\n", errno, strerror(errno));

  // ip(7)，地址
  // 注意sin_port参数，它是网络字节序的，这里设置的是9501端口
  // 9501（10进制）、00100101 00011101（2进制）、0x251d（16进制）、0x1d25（小端字节序）
  struct sockaddr_in serverAddr, clientAddr;
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = 0x1d25;
  serverAddr.sin_addr.s_addr = INADDR_ANY;

  int returnValue;

  // bind(2)，指定一个地址，绑定到socket上面
  returnValue = bind(sockfd, (struct sockaddr *)&serverAddr, sizeof(serverAddr));
  printf("bind returnValue=%d\r\n", returnValue);
  printf("errno=%d,%s\r\n", errno, strerror(errno));

  // listen(2)，监听
  // backlog参数定义sockfd的挂起连接队列的最大长度
  returnValue = listen(sockfd, 4);
  printf("listen returnValue=%d\r\n", returnValue);
  printf("errno=%d,%s\r\n", errno, strerror(errno));

  // accept(2)，接收socket连接
  socklen_t clientAddrLen = sizeof(clientAddr);
  int connfd = accept(sockfd, (struct sockaddr *)&clientAddr, &clientAddrLen);
  printf("client linked,connfd=%d\r\n", connfd);
  printf("errno=%d,%s\r\n", errno, strerror(errno));

  // recv(2)，从socket读取数据
  char msg[1024] = {0};
  ssize_t recvBytes = recv(connfd, msg, sizeof(msg), 0);
  printf("receive bytes=%d,msg=%s\r\n", recvBytes, msg);
  printf("errno=%d,%s\r\n", errno, strerror(errno));

  return 0;
}