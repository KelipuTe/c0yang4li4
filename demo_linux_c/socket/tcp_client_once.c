#include <errno.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>

// 一次性的htcp客户端
int main() {
  printf("tcp client start,pid=%d\r\n", getpid());

  int sockfd = socket(AF_INET, SOCK_STREAM, 0);

  struct sockaddr_in clientAddr;
  clientAddr.sin_family = AF_INET;
  clientAddr.sin_port = 0x1d25;
  clientAddr.sin_addr.s_addr = INADDR_ANY;

  // connect(2)，发起socket连接
  int returnValue = connect(sockfd, (struct sockaddr *)&clientAddr, sizeof(clientAddr));
  printf("connect returnValue=%d\r\n", returnValue);
  printf("errno=%d,%s\r\n", errno, strerror(errno));

  // send(2)，向socket发送数据
  ssize_t sendBytes = send(sockfd, "hello", 5, 0);
  printf("send bytes=%d\r\n", sendBytes);
  printf("errno=%d,%s\r\n", errno, strerror(errno));

  return 0;
}