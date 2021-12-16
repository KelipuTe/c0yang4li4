#include <netinet/in.h>
#include <netinet/tcp.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>

int main() {
  printf("tcp server start,pid=%d\r\n", getpid());

  int sockfd = socket(AF_INET, SOCK_STREAM, 0);

  struct sockaddr_in address, client;
  address.sin_family = AF_INET;
  // 9501（10进制）、0010 0101 0001 1101（2进制）、0x251d（16进制）、0x1d25（小端字节序）
  address.sin_port = 0x1d25;
  address.sin_addr.s_addr = INADDR_ANY;

  int ret = bind(sockfd, (struct sockaddr *)&address, sizeof(address));
  printf("bind ret=%d\r\n", ret);

  ret = listen(sockfd, 5);
  printf("listen ret=%d\r\n", ret);

  socklen_t client_len = sizeof(client);
  int connfd = accept(sockfd, (struct sockaddr *)&client, &client_len);
  printf("客户端连接上来了，它的connfd=%d\r\n", connfd);

  // 接受数据
  char msg[1024] = {0};
  ret = recv(connfd, msg, sizeof(msg), 0);
  printf("receive %d bytes,msg=%s\r\n", ret, msg);

  return 0;
}