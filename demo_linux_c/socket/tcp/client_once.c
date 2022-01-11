#include <errno.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

// 一次性的tcp客户端
int main() {
  printf("tcp client start,getpid()=%d\r\n", getpid());

  int sockfd = socket(AF_INET, SOCK_STREAM, 0);

  struct sockaddr_in clientAddr;
  clientAddr.sin_family = AF_INET;
  clientAddr.sin_port = 0x1d25;
  clientAddr.sin_addr.s_addr = INADDR_ANY;

  // connect(2)
  // #include <sys/socket.h>
  // 发起socket连接
  int rtvl1 = connect(sockfd, (struct sockaddr *)&clientAddr, sizeof(clientAddr));
  printf("connect(),rtvl1=%d\r\n", rtvl1);
  printf("errno=%d,%s\r\n", errno, strerror(errno));

  // send(2)
  // #include <sys/socket.h>
  // 向socket发送数据
  ssize_t rtvl2 = send(sockfd, "hello", 5, 0);
  printf("send(),rtvl2=%d\r\n", rtvl2);
  printf("errno=%d,%s\r\n", errno, strerror(errno));

  return 0;
}