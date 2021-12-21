#include "epoll.h"
#include "service.h"
#include <pthread.h>

static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *cell_event_loop(void *arg) {
  int cell_no = *(int *)arg;

  int epoll_fd = epoll_create(1024);

  if (-1 == epoll_fd) {
    printf("epoll_create failed\r\n");
    printf("errno=%d,%s\r\n", errno, strerror(errno));
    exit(0);
  }
  printf("cell_event_loop cell_no=%d\r\n", cell_no);
  reactor *cell = &service1.cell[cell_no];

  cell->epoll_fd = epoll_fd;
  //   event_set(EPOLLIN, service1.sockfd);

  struct epoll_event events[1024];
  printf("epoll_fd=%d\r\n", epoll_fd);
  while (1) {
    pthread_mutex_lock(&mutex);
    if (cell->current_client_num > 0) {
      for (int i = 0; i < 1024; i++) {
        if (cell->clientsBuffer[i].sockfd > 0) {
          for (int j = 0; j < 1024; j++) {
            if (cell->clients[j].sockfd == 0) {
              cell->clients[j] = cell->clientsBuffer[i];
              event_set(cell->epoll_fd, EPOLLIN, cell->clients[j].sockfd);
              break;
            }
          }
          cell->clientsBuffer[i].sockfd = 0;
        }
      }
      cell->current_client_num = 0;
    }
    pthread_mutex_unlock(&mutex);
    //   -1=阻塞调用，0=非阻塞，>0=等待几秒返回
    int ret_val = epoll_wait(cell->epoll_fd, events, 1024, 1);
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

        if (events[i].events == EPOLLIN) {

          char msg[1024] = {0};
          ssize_t recvBytes = recv(fd, msg, sizeof(msg), 0);
          printf("receive bytes=%d,msg=%s\r\n", recvBytes, msg);

          if (recvBytes > 0) {

            char resp[] = "HTTP/1.1 OK 200\r\nContent-Type: text/html\r\nContent-Length: 12\r\n\r\nhello, world";
            ssize_t sendBytes = send(fd, resp, sizeof(resp), 0);
            printf("send bytes=%d\r\n", sendBytes);
          } else {

            event_del(cell->epoll_fd, EPOLLIN, fd);
            close(fd);
          }
        }
      }
    }
  }
}

void add_connection(reactor *cell, connection client) {
  int i;
  pthread_mutex_lock(&mutex);
  for (i = 0; i < 1024; i++) {
    if (cell->clientsBuffer[i].sockfd == 0) {
      break;
    }
  }
  printf("add_connection,i=%d", i);
  cell->clientsBuffer[i] = client;
  cell->current_client_num++;
  pthread_mutex_unlock(&mutex);
}