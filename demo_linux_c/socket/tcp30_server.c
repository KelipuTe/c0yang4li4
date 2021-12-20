#include <arpa/inet.h>
#include <errno.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

// 可重用的http服务端
int main() {
  printf("tcp server start,pid=%d\r\n", getpid());

  int sockfd = socket(AF_INET, SOCK_STREAM, 0);

  struct sockaddr_in serverAddr, clientAddr;
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = htons(9501);
  serverAddr.sin_addr.s_addr = inet_addr("0.0.0.0");

  int returnValue;

  // setsockopt(2)，设置socket选项
  // int report = 1;
  // returnValue = setsockopt(sockfd, SOL_SOCKET, SO_REUSEPORT, &report, sizeof(report));
  // printf("setsockopt returnValue=%d\r\n", returnValue);
  // printf("errno=%d,%s\r\n", errno, strerror(errno));

  returnValue = bind(sockfd, (struct sockaddr *)&serverAddr, sizeof(serverAddr));
  printf("bind returnValue=%d", returnValue);

  returnValue = listen(sockfd, 5);
  printf("listen returnValue=%d\r\n", returnValue);

  while (1) {
    socklen_t clientAddrLen = sizeof(clientAddr);
    int connfd = accept(sockfd, (struct sockaddr *)&clientAddr, &clientAddrLen);
    printf("client linked,connfd=%d\r\n", connfd);

    char msg[1024] = {0};
    ssize_t recvBytes;
    while ((recvBytes = recv(connfd, msg, sizeof(msg), 0)) <= 0) {
      close(connfd);
      printf("client close,connfd=%d\r\n", connfd);
      break;
    }
    printf("receive bytes=%d,msg=%s\r\n", recvBytes, msg);

    // 返回http格式的数据
    char resp[] = "HTTP/1.1 OK 200\r\nContent-Type: text/html\r\nContent-Length: 12\r\n\r\nhello, world";
    ssize_t sendBytes = send(connfd, resp, sizeof(resp), 0);
    printf("send bytes=%d\r\n", sendBytes);

    // 清空本次获取到的数据
    memset(msg, 0, sizeof(msg));
  }

  return 0;
}