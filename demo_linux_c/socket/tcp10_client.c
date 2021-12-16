#include <netinet/in.h>
#include <netinet/tcp.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>

int main() {

  printf("tcp client start,pid=%d\r\n", getpid());

  int sockfd = socket(AF_INET, SOCK_STREAM, 0);

  struct sockaddr_in address, client;
  address.sin_family = AF_INET;
  address.sin_port = 0x1d25;
  address.sin_addr.s_addr = INADDR_ANY;

  int ret = connect(sockfd, (struct sockaddr *)&address, sizeof(address));

  printf("connect ret =%d\r\n", ret);

  // 发送数据
  ret = send(sockfd, "china", 5, 0);

  printf("send %d bytes\r\n", ret);

  return 0;
}