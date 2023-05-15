#include <errno.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

// 一次性的 tcp 客户端
int main() {
  printf("[debug]:tcp client start,getpid()=%d\n", getpid());

  int sockfd = socket(AF_INET, SOCK_STREAM, 0);

  struct sockaddr_in clientAddr;
  clientAddr.sin_family = AF_INET;
  clientAddr.sin_port = 0x1d25;
  clientAddr.sin_addr.s_addr = INADDR_ANY;

  // 发起 socket 连接
  int connectResult = connect(sockfd, (struct sockaddr *)&clientAddr, sizeof(clientAddr));
  printf("[debug]:connectResult=%d\n", connectResult);
  printf("[debug]:errno=%d, error=%s\n", errno, strerror(errno));

  // 向 socket 发送数据
  ssize_t sendByteNum = send(sockfd, "hello", 5, 0);
  printf("[debug]:sendByteNum=%ld\n", sendByteNum);
  printf("[debug]:errno=%d, error=%s\n", errno, strerror(errno));

  return 0;
}