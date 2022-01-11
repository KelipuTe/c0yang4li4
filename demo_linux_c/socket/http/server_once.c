#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>

// 一次性的http服务端
int main() {
  printf("tcp server start,getpid()=%d\r\n", getpid());

  int sockfd = socket(AF_INET, SOCK_STREAM, 0);

  struct sockaddr_in serverAddr;
  serverAddr.sin_family = AF_INET;
  // htons(3)
  // #include <arpa/inet.h>
  // 主机字节序转网络字节序
  serverAddr.sin_port = htons(9501);
  // inet_addr(3)
  // #include <sys/socket.h>
  // #include <netinet/in.h>
  // #include <arpa/inet.h>
  // 点分10进制转网络字节序
  serverAddr.sin_addr.s_addr = inet_addr("0.0.0.0");

  int rtvl1 = bind(sockfd, (struct sockaddr *)&serverAddr, sizeof(serverAddr));
  printf("bind(),rtvl1=%d\r\n", rtvl1);
  int rtvl2 = listen(sockfd, 2);
  printf("listen(),rtvl2=%d\r\n", rtvl2);
  struct sockaddr_in clientAddr;
  socklen_t clientAddrLen = sizeof(clientAddr);
  int connfd = accept(sockfd, (struct sockaddr *)&clientAddr, &clientAddrLen);
  printf("accept(),connfd=%d\r\n", connfd);
  char msg[1024] = {0};
  ssize_t rtvl3 = recv(connfd, msg, sizeof(msg), 0);
  printf("recv()=%d,msg=%s\r\n", rtvl3, msg);

  // 返回http格式的数据
  char arr1resp[] = "HTTP/1.1 OK 200\r\nContent-Type: text/html\r\nContent-Length: 12\r\n\r\nhello, world";
  ssize_t rtvl4 = send(connfd, arr1resp, sizeof(arr1resp), 0);
  printf("send(),rtvl4=%d\r\n", rtvl4);

  return 0;
}