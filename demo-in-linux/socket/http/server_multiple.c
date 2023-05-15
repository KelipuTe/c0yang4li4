#include <arpa/inet.h>
#include <errno.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

// 可重用的http服务端
int main() {
  printf("[debug]:tcp server start,getpid()=%d\n", getpid());

  int sockfd = socket(AF_INET, SOCK_STREAM, 0);

  struct sockaddr_in serverAddr;
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = htons(9501);
  serverAddr.sin_addr.s_addr = inet_addr("0.0.0.0");

  // 设置 socket 选项
  int report = 1;
  int setsockoptResult = setsockopt(sockfd, SOL_SOCKET, SO_REUSEPORT, &report, sizeof(report));
  printf("[debug]:setsockoptResult=%d\n", setsockoptResult);
  printf("[debug]:errno=%d, error=%s\n", errno, strerror(errno));

  int bindResult = bind(sockfd, (struct sockaddr *)&serverAddr, sizeof(serverAddr));
  printf("[debug]:bindResult=%d\n", bindResult);

  int listenResult = listen(sockfd, 2);
  printf("[debug]:listenResult=%d\n", listenResult);

  struct sockaddr_in clientAddr;
  while (1) {
    socklen_t clientAddrLen = sizeof(clientAddr);
    int connfd = accept(sockfd, (struct sockaddr *)&clientAddr, &clientAddrLen);
    printf("[debug]:connfd=%d\n", sockfd);

    char msg[1024] = {0};
    ssize_t recvByteNum = 0;
    recvByteNum = recv(connfd, msg, sizeof(msg), 0);
    printf("[debug]:recvByteNum=%ld, msg=%s\n", recvByteNum, msg);
    if (recvByteNum <= 0) {
      close(connfd);
      printf("[debug]:close(), connfd=%d\n", connfd);
    }

    char arr1resp[] = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\nConnection: keep-alive\r\nContent-Length: 12\r\n\r\nhello, world";
    ssize_t sendByteNum = send(connfd, arr1resp, sizeof(arr1resp), 0);
    printf("[debug]:sendByteNum=%ld\n", sendByteNum);

    // 清空本次获取到的数据
    memset(msg, 0, sizeof(msg));
  }

  return 0;
}