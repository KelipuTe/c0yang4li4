#include "service.h"
#include "connection.h"
#include "epoll.h"
#include "reactor.h"
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
  if (connfd > 0) {
    service1.call_num++;
    reactor *cell = &service1.cell[service1.call_num % service1.thread_num];

    struct connection client;
    client.sockfd = connfd;
    client.port = ntohs(clientAddr.sin_port);
    strcpy(client.ip, inet_ntoa(clientAddr.sin_addr));
    client.recv_buffer = (char *)malloc(sizeof(char) * 1024);
    client.recv_max_bytes = 1024;
    client.recv_last = 0;
    client.send_buffer = (char *)malloc(sizeof(char) * 1024);
    client.send_max_bytes = 1024;
    client.send_last = 0;

    add_connection(cell, client);
    // event_set(service1.epoll_fd, EPOLLIN, connfd);
  }
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
  event_set(service1.epoll_fd, EPOLLIN, service1.sockfd);

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

  service1.cell = (reactor *)malloc(sizeof(reactor) * service1.thread_num);

  for (int i = 0; i < service1.thread_num; i++) {
    service1.cell[i].cell_no = i;
    service1.cell[i].current_client_num = 0;
    service1.cell[i].max_client_num = 1024;
    service1.cell[i].clients = (connection *)malloc(sizeof(connection) * 1024);
    service1.cell[i].clientsBuffer = (connection *)malloc(sizeof(connection) * 1024);
    create_thread(cell_event_loop, &service1.cell[i].cell_no);
  }
}