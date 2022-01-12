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
  printf("tcp server start,getpid()=%d\r\n", getpid());

  int sockfd = socket(AF_INET, SOCK_STREAM, 0);

  struct sockaddr_in serverAddr;
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = htons(9501);
  serverAddr.sin_addr.s_addr = inet_addr("0.0.0.0");

  // setsockopt(2)
  // #include <sys/socket.h>
  // 设置socket选项
  int report = 1;
  int rtvl5 = setsockopt(sockfd, SOL_SOCKET, SO_REUSEPORT, &report, sizeof(report));
  printf("setsockopt(),rtvl5=%d\r\n", rtvl5);
  printf("errno=%d,%s\r\n", errno, strerror(errno));

  int rtvl1 = bind(sockfd, (struct sockaddr *)&serverAddr, sizeof(serverAddr));
  printf("bind(),rtvl1=%d\r\n", rtvl1);
  int rtvl2 = listen(sockfd, 2);
  printf("listen(),rtvl2=%d\r\n", rtvl2);

  struct sockaddr_in clientAddr;
  while (1) {
    socklen_t clientAddrLen = sizeof(clientAddr);
    int connfd = accept(sockfd, (struct sockaddr *)&clientAddr, &clientAddrLen);
    printf("accept(),connfd=%d\r\n", connfd);

    char msg[1024] = {0};
    ssize_t rtvl3 = 0;
    rtvl3 = recv(connfd, msg, sizeof(msg), 0);
    printf("recv()=%d,msg=%s\r\n", rtvl3, msg);
    if (rtvl3 <= 0) {
      close(connfd);
      printf("close(),connfd=%d\r\n", connfd);
    }

    // 返回http格式的数据
    char arr1resp[] = "HTTP/1.1 OK 200\r\nContent-Type: text/html\r\nContent-Length: 12\r\n\r\nhello, world";
    ssize_t rtvl4 = send(connfd, arr1resp, sizeof(arr1resp), 0);
    printf("send(),rtvl4=%d\r\n", rtvl4);

    // 清空本次获取到的数据
    memset(msg, 0, sizeof(msg));
  }

  return 0;
}