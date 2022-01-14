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

// IO多路复用
int main() {
  printf("tcp server start,getpid()=%d\r\n", getpid());

  int sockfd = socket(AF_INET, SOCK_STREAM, 0);

  struct sockaddr_in serverAddr;
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = htons(9501);
  serverAddr.sin_addr.s_addr = inet_addr("0.0.0.0");

  int rtvl1 = bind(sockfd, (struct sockaddr *)&serverAddr, sizeof(serverAddr));
  printf("bind(),rtvl1=%d\r\n", rtvl1);
  printf("errno=%d,%s\r\n", errno, strerror(errno));

  int rtvl2 = listen(sockfd, 1024);
  printf("listen(),rtvl2=%d\r\n", rtvl2);
  printf("errno=%d,%s\r\n", errno, strerror(errno));

  // epoll_create(2)
  // #include <sys/epoll.h>
  // 创建一个epoll文件描述符，epoll文件描述符关联linux内核事件表
  // epoll底层是红黑树实现的，创建的epoll文件描述符可以在`/proc/{pid}/fd/`目录下看到
  // 在使用完epoll后，必须调用close()关闭，否则可能导致fd被耗尽。
  int epoll_fd = epoll_create(1024);
  if (-1 == epoll_fd) {
    printf("epoll_create(),failed\r\n");
    printf("errno=%d,%s\r\n", errno, strerror(errno));
    exit(0);
  }

  // epoll_ctl(2)
  // #include <sys/epoll.h>
  // epoll_ctl()可用于添加、修改、删除epoll文件描述符关联的linux内核事件
  // 这里需要把监听的socket添加到epoll中，并关注可读事件
  // event参数是epoll_event结构体，epoll_event结构体的events参数=EPOLLIN，表示要关注的是可读事件
  // 可读事件发生的情况，客户端连接，客户端断开，异常，客户端发送数据并且达到内核的相关设置（接收水位标志）
  struct epoll_event event;
  event.events = EPOLLIN;
  event.data.fd = sockfd;
  int rtvl3 = epoll_ctl(epoll_fd, EPOLL_CTL_ADD, sockfd, &event);
  printf("epoll_ctl(),rtvl3=%d\r\n", rtvl3);
  printf("errno=%d,%s\r\n", errno, strerror(errno));

  struct epoll_event events[1024];
  while (1) {
    // 持续等待epoll文件描述符上的事件

    // epoll_wait(2)
    // #include <sys/epoll.h>
    // epoll_wait()可以等待epfd参数对应的epoll文件描述符上的事件
    // 如果有事件，则会以数组的形式放到events参数里
    // timeout参数可以控制等待的方式，-1=阻塞调用，0=非阻塞，>0=等待几秒返回
    // 如果函数执行成功的话，返回值就是得到的事件的数量
    int rtvl4 = epoll_wait(epoll_fd, events, 1024, -1);
    printf("epoll_wait(),rtvl4=%d\r\n", rtvl4);
    printf("errno=%d,%s\r\n", errno, strerror(errno));

    if (rtvl4 < 0) {
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

    if (rtvl4 > 0) {
      // 处理事件
      for (int i = 0; i < rtvl4; i++) {
        // 拿到这个事件对应的文件描述符
        int fd = events[i].data.fd;
        if (EPOLLIN == events[i].events) {
          // 识别可读事件
          if (fd == sockfd) {
            // 如果这个事件对应的文件描述符，就是socket的文件描述符
            // 那就说明这个事件是客户端连接事件，下面的流程就是tcp的客户端连接的流程了
            struct sockaddr_in clientAddr;
            socklen_t clientAddrLen = sizeof(clientAddr);
            int connfd = accept(sockfd, (struct sockaddr *)&clientAddr, &clientAddrLen);
            printf("accept(),connfd=%d\r\n", connfd);
            printf("errno=%d,%s\r\n", errno, strerror(errno));

            // 把connfd连接文件描述符也添加到epoll中，并关注可读事件
            struct epoll_event event;
            event.events = EPOLLIN;
            event.data.fd = connfd;
            int rtvl5 = epoll_ctl(epoll_fd, EPOLL_CTL_ADD, connfd, &event);
            printf("epoll_ctl(),rtvl5=%d\r\n", rtvl5);
            printf("errno=%d,%s\r\n", errno, strerror(errno));
          } else {
            // 这个示例的情况比较简单，如果不是socket的文件描述符，那就是connfd连接的文件描述符
            // 下面的流程就是tcp的服务端从socket读取数据和响应数据给客户端的流程了
            char msg[1024] = {0};
            ssize_t rtvl6 = recv(fd, msg, sizeof(msg), 0);
            printf("recv(),rtvl6=%d,msg=%s\r\n", rtvl6, msg);
            printf("errno=%d,%s\r\n", errno, strerror(errno));
            if (rtvl6 > 0) {
              char resp[] = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\nConnection: keep-alive\r\nContent-Length: 12\r\n\r\nhello, world";
              ssize_t rtvl7 = send(fd, resp, sizeof(resp), 0);
              printf("send(),rtvl7=%d\r\n", rtvl7);
              printf("errno=%d,%s\r\n", errno, strerror(errno));
            } else {
              // 如果判断出对方已关闭，就把connfd连接文件描述符从epoll中删除
              int rtvl8 = epoll_ctl(epoll_fd, EPOLL_CTL_DEL, fd, NULL);
              printf("epoll_ctl(),rtvl8=%d\r\n", rtvl8);
              printf("errno=%d,%s\r\n", errno, strerror(errno));
            }
          }
        }
      }
    }
  }

  return 0;
}