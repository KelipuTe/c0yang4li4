#include <errno.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

// 一次性的 tcp 服务端
int main() {
  printf("[debug]:tcp server start,getpid()=%d\n", getpid());

  int sockfd = socket(AF_INET, SOCK_STREAM, 0);
  printf("[debug]:sockfd=%d\n", sockfd);
  printf("[debug]:errno=%d, error=%s\n", errno, strerror(errno));

  // 设置 ip 地址和端口
  // sin_port 参数是网络字节序的，这里设置的是 9501 端口
  // INADDR_ANY 表示 0.0.0.0 地址
  struct sockaddr_in serverAddr;
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = 0x1d25;
  serverAddr.sin_addr.s_addr = INADDR_ANY;

  // 把上面设置的地址，绑定到 socket 上面
  int bindResult = bind(sockfd, (struct sockaddr *)&serverAddr, sizeof(serverAddr));
  printf("[debug]:bindResult=%d\n", bindResult);
  printf("[debug]:errno=%d, error=%s\n", errno, strerror(errno));

  // 监听 socket
  // backlog 参数定义 sockfd 的挂起连接队列的最大长度
  int listenResult = listen(sockfd, 2);
  printf("[debug]:listenResult=%d\n", listenResult);
  printf("[debug]:errno=%d, error=%s\n", errno, strerror(errno));

  // 接收 socket 连接
  struct sockaddr_in clientAddr;
  socklen_t clientAddrLen = sizeof(clientAddr);
  int connfd = accept(sockfd, (struct sockaddr *)&clientAddr, &clientAddrLen);
  printf("[debug]:connfd=%d\n", sockfd);
  printf("[debug]:errno=%d, error=%s\n", errno, strerror(errno));

  // 从 socket 读取数据
  char msg[1024] = {0};
  ssize_t recvByteNum = recv(connfd, msg, sizeof(msg), 0);
  printf("[debug]:recvByteNum=%ld, msg=%s\n", recvByteNum, msg);
  printf("[debug]:errno=%d, error=%s\n", errno, strerror(errno));

  return 0;
}