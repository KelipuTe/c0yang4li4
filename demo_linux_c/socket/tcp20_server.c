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
  address.sin_port = htons(9501);
  address.sin_addr.s_addr = INADDR_ANY;

  //struct sockaddr_in address,client;
  //address.sin_family = AF_INET;
  //address.sin_port = htons(9501);
  //address.sin_addr.s_addr = inet_addr("0.0.0.0");

  int ret = bind(sockfd, (struct sockaddr *)&address, sizeof(address));

  printf("bind ret=%d\r\n", ret);

  ret = listen(sockfd, 5);

  printf("listen ret=%d\r\n", ret);

  //int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
  socklen_t client_len = sizeof(client);
  int connfd = accept(sockfd, (struct sockaddr *)&client, &client_len);

  printf("客户端连接上来了，它的connfd=%d\r\n", connfd);

  char msg[1024] = {0};

  ret = recv(connfd, msg, sizeof(msg), 0);

  printf("receive %d bytes,msg=%s\r\n", ret, msg);

  // 返回数据
  char resp[] = "HTTP/1.1 OK 200\r\nContent-Type: text/html\r\nContent-Length: 10\r\n\r\nHelloWorld";
  ret = send(connfd, resp, sizeof(resp), 0);
  printf("send %d bytes\r\n", ret);

  return 0;
}