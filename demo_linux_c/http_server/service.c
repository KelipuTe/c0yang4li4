#include "service.h"
#include "epoll.h"
#include "thread.h"

void my_init_socket() {
  int sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0) {
    printf("socket failed\r\n");
    exit(0);
  }

  service1.sockfd = sockfd;
}

void my_bind() {
  struct sockaddr_in serverAddr;
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = htons(service1.port);
  serverAddr.sin_addr.s_addr = inet_addr(service1.ip);

  int ret = 1;
  if (setsockopt(service1.sockfd, SOL_SOCKET, SO_REUSEPORT, &ret, sizeof(ret)) != 0) {
    printf("setsockopt failed\r\n");
  }

  ret = bind(service1.sockfd, (struct sockaddr *)&serverAddr, sizeof(serverAddr));
  if (ret == -1) {
    printf("bind failed\r\n");
    exit(0);
  }
}

void my_listen() {
  int returnValue = listen(service1.sockfd, service1.backlog);
  if (returnValue == -1) {
    printf("listen returnValue=%d\r\n", returnValue);
    exit(0);
  }
  printf("listen success\r\n");
}

void my_accept() {
  struct sockaddr_in clientAddr;
  socklen_t clientAddrLen = sizeof(clientAddr);
  int connfd = accept(service1.sockfd, (struct sockaddr *)&clientAddr, &clientAddrLen);
  printf("client linked,connfd=%d\r\n", connfd);

  event_set(EPOLLIN, connfd);
}

void *event_loop() {
  // epoll_create(2)，创建一个epoll文件描述符，关联内核事件表，红黑树实现
  int epoll_fd = epoll_create(1024);

  if (-1 == epoll_fd) {
    printf("epoll_create failed\r\n");
    printf("errno=%d,%s\r\n", errno, strerror(errno));
    exit(0);
  }

  service1.epoll_fd = epoll_fd;
  event_set(EPOLLIN, service1.sockfd);

  struct epoll_event events[1024];

  while (1) {
    //   -1=阻塞调用，0=非阻塞，>0=等待几秒返回
    int ret_val = epoll_wait(epoll_fd, events, 1024, -1);

    if (ret_val < 0) {
      if (errno == EINTR) {
        //   这种情况不应该退出
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
          if (fd == service1.sockfd) {
            my_accept();
          } else {
            char msg[1024] = {0};
            ssize_t recvBytes = recv(fd, msg, sizeof(msg), 0);
            printf("receive bytes=%d,msg=%s\r\n", recvBytes, msg);

            if (recvBytes > 0) {

              char resp[] = "HTTP/1.1 OK 200\r\nContent-Type: text/html\r\nContent-Length: 12\r\n\r\nhello, world";
              ssize_t sendBytes = send(fd, resp, sizeof(resp), 0);
              printf("send bytes=%d\r\n", sendBytes);
            } else {
              close(fd);
              event_del(EPOLLIN, fd);
            }
          }
        }
      }
    }
  }
}

void my_run() {
  // 启动一个线程监听socket
  // 启动thread_num个线程lianjiesocket

  create_thread(event_loop, NULL);
}