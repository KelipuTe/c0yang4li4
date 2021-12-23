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
          connection *client = find_connection(cell, fd);
          printf("find_connection=%p\r\n", client);
          int recvBytes = recv_data(client);
          /**收到数据，要处理，并且要清理一下接收缓冲区的内容***/
          printf("recv msg=%s\r\n", client->recv_buffer);
          memset(client->recv_buffer, 0, sizeof(client->recv_buffer));
          client->recv_last = 0;
          /**收到数据，要处理，并且要清理一下接收缓冲区的内容***/
          if (recvBytes == -1) {
            remove_client(cell, client);
          } else {
            char resp[] = "HTTP/1.1 OK 200\r\nContent-Type: text/html\r\nContent-Length: 12\r\n\r\nhello, world";
            push_data(client, resp, strlen(resp));

            int writeRet = write_data(client);
            if (writeRet == -1) {
              remove_client(cell, client);

            } else if (writeRet > 0) {
              write_data(client);
              event_set2(cell->epoll_fd, EPOLLOUT | EPOLLIN, client->sockfd);
            }
          }
        }
        if (events[i].events == EPOLLOUT) {
          connection *client = find_connection(cell, fd);
          int writeRet = write_data(client);

          if (writeRet == -1) {
            remove_client(cell, client);
          } else if (writeRet == 0) {
            event_set2(cell->epoll_fd, EPOLLIN, client->sockfd);
          }
        }
      }
    }
  }
}

void remove_client(reactor *cell, connection *client) {
  client->recv_last = 0;
  client->send_last = 0;
  client->recv_buffer_full = 0;
  client->send_buffer_full = 0;
  client->recv_max_bytes = 0;
  client->send_max_bytes = 0;
  memset(client->recv_buffer, 0, sizeof(client->recv_buffer));
  memset(client->send_buffer, 0, sizeof(client->recv_buffer));
  event_del(cell->epoll_fd, EPOLLIN, client->sockfd);
  close(client->sockfd);
  printf("client closed=%d", client->sockfd);
  client->sockfd = 0;
}

connection *find_connection(reactor *cell, int fd) {
  if (0 == fd) {
    return NULL;
  }
  for (int i = 0; i < 1024; i++) {
    if (cell->clients[i].sockfd == fd) {
      return &cell->clients[i];
    }
  }
  return NULL;
}

void add_connection(reactor *cell, connection client) {
  int i;
  pthread_mutex_lock(&mutex);
  for (i = 0; i < 1024; i++) {
    if (cell->clientsBuffer[i].sockfd == 0) {
      break;
    }
  }
  // printf("add_connection,i=%d", i);
  cell->clientsBuffer[i] = client;
  cell->current_client_num++;
  pthread_mutex_unlock(&mutex);
}