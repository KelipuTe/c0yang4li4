#include <arpa/inet.h>
#include <errno.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <unistd.h>

// IO 多路复用
int main() {
  printf("[debug]:tcp server start, getpid()=%d\n", getpid());

  int sockfd = socket(AF_INET, SOCK_STREAM, 0);

  struct sockaddr_in serverAddr;
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = htons(9501);
  serverAddr.sin_addr.s_addr = inet_addr("0.0.0.0");

  int bindResult = bind(sockfd, (struct sockaddr *)&serverAddr, sizeof(serverAddr));
  printf("[debug]:bindResult=%d\n", bindResult);

  int listenResult = listen(sockfd, 1024);
  printf("[debug]:listenResult=%d\n", listenResult);

  // 创建 epoll 文件描述符
  int epollFD = epoll_create(1024);
  if (-1 == epollFD) {
    printf("[debug]:epoll_create(), failed\n");
    printf("[debug]:errno=%d, error=%s\n", errno, strerror(errno));
    exit(0);
  }

  // 让 epoll 去监听 socket 上的 EPOLLIN 事件
  struct epoll_event event;
  event.events = EPOLLIN;
  event.data.fd = sockfd;
  int epollCtlResult = epoll_ctl(epollFD, EPOLL_CTL_ADD, sockfd, &event);
  printf("[debug]:epollCtlResult=%d\n", epollCtlResult);
  printf("[debug]:errno=%d, error=%s\n", errno, strerror(errno));

  struct epoll_event a5epollEvent[1024];
  while (1) {
    // 持续等待 epoll 文件描述符上的事件
    int epollWaitResult = epoll_wait(epollFD, a5epollEvent, 1024, -1);
    printf("[debug]:epollWaitResult=%d\n", epollWaitResult);
    printf("[debug]:errno=%d, error=%s\n", errno, strerror(errno));

    if (epollWaitResult < 0) {
      // 处理异常
      if (EINTR == errno) {
        // 这里需要判断错误是不是EINTR中断信号，这是预料之内的错误，所以应该继续epoll_wait()
        // 如果用`strace`命令追踪的话，会得到像下面这样的输出
        // epoll_wait(4, 0x7ffe9e5feda0, 1024, -1) = -1 EINTR (Interrupted system call)
        continue;
      } else {
        break;
      }
    }

    if (epollWaitResult > 0) {
      // 处理事件
      for (int i = 0; i < epollWaitResult; i++) {
        // 拿到这个事件对应的文件描述符
        int fd = a5epollEvent[i].data.fd;
        if (EPOLLIN == a5epollEvent[i].events) {
          if (fd == sockfd) {
            // 如果事件对应的文件描述符，就是 socket 的文件描述符
            // 那就说明这个事件是客户端连接，下面的流程就是 TCP 的客户端连接的流程了
            struct sockaddr_in clientAddr;
            socklen_t clientAddrLen = sizeof(clientAddr);
            int connfd = accept(sockfd, (struct sockaddr *)&clientAddr, &clientAddrLen);
            printf("[debug]:connfd=%d\n", connfd);
            printf("[debug]:errno=%d, error=%s\n", errno, strerror(errno));

            // 把 TCP 连接的 connfd 文件描述符也添加到 epoll 中，并关注 EPOLLIN 事件
            struct epoll_event event;
            event.events = EPOLLIN;
            event.data.fd = connfd;
            epollCtlResult = epoll_ctl(epollFD, EPOLL_CTL_ADD, connfd, &event);
            printf("[debug]:epollCtlResult=%d\n", epollCtlResult);
            printf("[debug]:errno=%d, error=%s\n", errno, strerror(errno));
          } else {
            // 这个示例的情况比较简单，如果不是 socket 的文件描述符，那就是 connfd 文件描述符
            // 下面的流程就是 TCP 的服务端从 socket 读取数据和响应数据给客户端的流程了
            char msg[1024] = {0};
            ssize_t recvByteNum = recv(fd, msg, sizeof(msg), 0);
            printf("[into]:recvByteNum=%ld, msg=%s\n", recvByteNum, msg);
            printf("[debug]:errno=%d, error=%s\n", errno, strerror(errno));
            if (recvByteNum > 0) {
              char resp[] = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\nConnection: keep-alive\r\nContent-Length: 12\n\r\nhello, world";
              ssize_t sendByteNum = send(fd, resp, sizeof(resp), 0);
              printf("[into]:sendByteNum=%ld\n", sendByteNum);
              printf("[debug]:errno=%d, error=%s\n", errno, strerror(errno));
            } else {
              // 如果判断出对方已关闭，就把 TCP 连接的 connfd 文件描述符从 epoll 中删除
              epollCtlResult = epoll_ctl(epollFD, EPOLL_CTL_DEL, fd, NULL);
              printf("[debug]:epollCtlResult=%d\n", epollCtlResult);
              printf("[debug]:errno=%d, error=%s\n", errno, strerror(errno));
            }
          }
        }
      }
    }
  }

  return 0;
}