#include <arpa/inet.h>
#include <errno.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

int main() {

  printf("tcp server start,pid=%d\r\n", getpid());

  int sockfd = socket(AF_INET, SOCK_STREAM, 0);

  struct sockaddr_in address, client;
  address.sin_family = AF_INET;
  address.sin_port = htons(9501);
  address.sin_addr.s_addr = inet_addr("0.0.0.0");

  //   int setsockopt(int sockfd, int level, int optname,
  //                  const void *optval, socklen_t optlen);
  //   int report = 1;
  //   if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEPORT, &report, sizeof(report)) != 0) {
  //     printf("设置socket选项失败\r\n");
  //   }

  int ret = bind(sockfd, (struct sockaddr *)&address, sizeof(address));

  printf("bind ret=%d,errno=%d,error=%s\r\n", ret, errno, strerror(errno));

  ret = listen(sockfd, 5);

  printf("listen ret=%d\r\n", ret);

  while (1) {
    //int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
    socklen_t client_len = sizeof(client);
    int connfd = accept(sockfd, (struct sockaddr *)&client, &client_len);

    printf("客户端连接上来了，它的connfd=%d\r\n", connfd);

    char msg[1024] = {0};

    while ((ret = recv(connfd, msg, sizeof(msg), 0)) <= 0) {

      close(connfd);
      printf("客户端进程关闭了连接\r\n");
      break;
    }

    printf("receive %d bytes,msg=%s\r\n", ret, msg);

    memset(msg, 0, sizeof(msg));

    char resp[] = "HTTP/1.1 OK 200\r\nContent-Type: text/html\r\nContent-Length: 10\r\n\r\nHelloWorld";
    ret = send(connfd, resp, sizeof(resp), 0);
    printf("send %d bytes\r\n", ret);
  }

  return 0;
}