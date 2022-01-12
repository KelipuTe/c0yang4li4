#include <errno.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

// 一次性的htcp服务端
int main() {
  printf("tcp server start,getpid()=%d\r\n", getpid());

  // socket(2)
  // #include <sys/socket.h>
  // socket初始化
  // __family参数，AF_INET表示ipv4
  // __type参数，SOCK_STREAM表示tcp
  // __protocol参数一般给0
  int sockfd = socket(AF_INET, SOCK_STREAM, 0);
  // __type参数，可以有多个选项，SOCK_NONBLOCK=非阻塞模式，调用recv()时不会阻塞
  // int sockfd = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, 0);
  printf("errno=%d,%s\r\n", errno, strerror(errno));

  // ip(7)
  // 设置ip地址和端口
  // 注意sin_port参数，它是网络字节序的，这里设置的是9501端口
  // 9501（10进制）、00100101 00011101（2进制）、0x251d（16进制）、0x1d25（小端字节序）
  struct sockaddr_in serverAddr;
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = 0x1d25;
  serverAddr.sin_addr.s_addr = INADDR_ANY;

  // bind(2)
  // #include <sys/socket.h>
  // 把上面设置的地址，绑定到socket上面
  int rtvl1 = bind(sockfd, (struct sockaddr *)&serverAddr, sizeof(serverAddr));
  printf("bind(),rtvl1=%d\r\n", rtvl1);
  printf("errno=%d,%s\r\n", errno, strerror(errno));

  // listen(2)
  // #include <sys/socket.h>
  // 监听socket
  // backlog参数定义sockfd的挂起连接队列的最大长度
  int rtvl2 = listen(sockfd, 2);
  printf("listen(),rtvl2=%d\r\n", rtvl2);
  printf("errno=%d,%s\r\n", errno, strerror(errno));

  // accept(2)
  // #include <sys/socket.h>
  // 接收socket连接
  struct sockaddr_in clientAddr;
  socklen_t clientAddrLen = sizeof(clientAddr);
  int connfd = accept(sockfd, (struct sockaddr *)&clientAddr, &clientAddrLen);
  printf("accept(),connfd=%d\r\n", connfd);
  printf("errno=%d,%s\r\n", errno, strerror(errno));

  // recv(2)
  // #include <sys/socket.h>
  // 从socket读取数据
  char msg[1024] = {0};
  ssize_t rtvl3 = recv(connfd, msg, sizeof(msg), 0);
  printf("recv()=%d,msg=%s\r\n", rtvl3, msg);
  printf("errno=%d,%s\r\n", errno, strerror(errno));

  return 0;
}