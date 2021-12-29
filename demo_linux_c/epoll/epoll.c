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

// 一次性的http服务端
int main() {
  printf("tcp server start,pid=%d\r\n", getpid());

  int sockfd = socket(AF_INET, SOCK_STREAM, 0);

  struct sockaddr_in serverAddr, clientAddr;
  serverAddr.sin_family = AF_INET;
  // htons(3)，主机字节序转网络字节序
  serverAddr.sin_port = htons(9501);
  // inet_addr(3)，点分10进制转网络字节序
  serverAddr.sin_addr.s_addr = inet_addr("0.0.0.0");

  int returnValue;

  returnValue = bind(sockfd, (struct sockaddr *)&serverAddr, sizeof(serverAddr));
  printf("bind returnValue=%d\r\n", returnValue);

  returnValue = listen(sockfd, 4);
  printf("listen returnValue=%d\r\n", returnValue);
  // epoll_create(2)，创建一个epoll文件描述符，关联内核事件表，红黑树实现
  int epoll_fd = epoll_create(1024);

  if (-1 == epoll_fd) {
    printf("epoll_create failed\r\n");
    printf("errno=%d,%s\r\n", errno, strerror(errno));
    exit(0);
  }

  struct epoll_event event;
  event.events = EPOLLIN;
  event.data.fd = sockfd;

  // 把sockfd监听的socket添加到epoll内核事件表中，文件sockfd要关注的是可读事件
  // 可读事件发生的情况，客户端连接，客户端断开，异常，客户端发送数据并且达到内核的相关设置（接收水位标志）
  int ret_val = epoll_ctl(epoll_fd, EPOLL_CTL_ADD, sockfd, &event);

  struct epoll_event events[1024];

  while (1) {
    //   -1=阻塞调用，0=非阻塞，>0=等待几秒返回
    ret_val = epoll_wait(epoll_fd, events, 1024, -1);

    if (ret_val < 0) {
      if (errno == EINTR) {
        //   这种情况不应该退出
        // 这里需要判断错误是不是EINTR中断信号，这是预料之内的错误，所以应该继续epoll_wait
        // epoll_wait(4, 0x7ffe9e5feda0, 1024, -1) = -1 EINTR (Interrupted system call)
        continue;
      } else {
        break;
      }
    }
    if (ret_val > 0) {
      for (int i = 0; i < ret_val; i++) {
        int fd = events[i].data.fd;

        // 有客户端连接上来
        if (events[i].events == EPOLLIN) {
          if (fd == sockfd) {
            socklen_t clientAddrLen = sizeof(clientAddr);
            int connfd = accept(sockfd, (struct sockaddr *)&clientAddr, &clientAddrLen);
            printf("client linked,connfd=%d\r\n", connfd);

            struct epoll_event event;
            event.events = EPOLLIN;
            event.data.fd = connfd;

            int ret_val = epoll_ctl(epoll_fd, EPOLL_CTL_ADD, connfd, &event);
          } else {
            char msg[1024] = {0};
            ssize_t recvBytes = recv(fd, msg, sizeof(msg), 0);
            printf("receive bytes=%d,msg=%s\r\n", recvBytes, msg);

            if (recvBytes > 0) {

              char resp[] = "HTTP/1.1 OK 200\r\nContent-Type: text/html\r\nContent-Length: 12\r\nConnection: keep-alive\r\n\r\nhello, world";
              ssize_t sendBytes = send(fd, resp, sizeof(resp), 0);
              printf("send bytes=%d\r\n", sendBytes);
            } else {
              int ret_val = epoll_ctl(epoll_fd, EPOLL_CTL_DEL, fd, NULL);
            }
          }
        }
      }
    }
  }

  return 0;
}