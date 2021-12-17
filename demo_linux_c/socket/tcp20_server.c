#include <netinet/in.h>
#include <netinet/tcp.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>

// 一次性的http服务端
int main() {
  printf("tcp server start,pid=%d\r\n", getpid());

  int sockfd = socket(AF_INET, SOCK_STREAM, 0);

  struct sockaddr_in serverAddr, clientAddr;
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = htons(9501);
  serverAddr.sin_addr.s_addr = inet_addr("0.0.0.0");
  
int returnValue;

   returnValue = bind(sockfd, (struct sockaddr *)&serverAddr, sizeof(serverAddr));
  printf("bind returnValue=%d\r\n", returnValue);

  returnValue = listen(sockfd,4);
  printf("listen returnValue=%d\r\n", returnValue);

  socklen_t clientAddrLen = sizeof(clientAddr);
  int connfd = accept(sockfd, (struct sockaddr *)&clientAddr, &clientAddrLen);
  printf("client linked,connfd=%d\r\n", connfd);

  char msg[1024] = {0};
  returnValue = recv(connfd, msg, sizeof(msg), 0);
  printf("receive bytes=%d,msg=%s\r\n", returnValue, msg);

  // 返回http格式的数据
  char resp[] = "HTTP/1.1 OK 200\r\nContent-Type: text/html\r\nContent-Length: 12\r\n\r\nhello, world";
  returnValue = send(connfd, resp, sizeof(resp), 0);
  printf("send bytes=%d\r\n", returnValue);

  return 0;
}