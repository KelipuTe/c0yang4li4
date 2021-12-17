#include <netinet/in.h>
#include <netinet/tcp.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>
#include <errno.h>

// tcp客户端
int main() {
  printf("tcp client start,pid=%d\r\n", getpid());

  int sockfd = socket(AF_INET, SOCK_STREAM, 0);

  struct sockaddr_in clientAddr;
  clientAddr.sin_family = AF_INET;
  clientAddr.sin_port = 0x1d25;
  clientAddr.sin_addr.s_addr = INADDR_ANY;

int returnValue;

// 发起socket连接，connect(2)
   returnValue = connect(sockfd, (struct sockaddr *)&clientAddr, sizeof(clientAddr));
  printf("connect returnValue=%d\r\n", returnValue);
  printf("errno=%d,%s\r\n", errno, strerror(errno));

  // 向socket发送数据，send(2)
  returnValue = send(sockfd, "hello", 5, 0);
  printf("send bytes=%d\r\n", returnValue);
  printf("errno=%d,%s\r\n", errno, strerror(errno));

  return 0;
}