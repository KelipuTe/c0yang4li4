#include "epoll.h"
#include "service.h"
#include <pthread.h>

static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void connection_add(reactor *cell, connection conn) {
  pthread_mutex_lock(&mutex);

  // 找到连接线程client连接缓冲区中的空位，把这个client连接存下来
  int i = 0;
  while (i < 1024) {
    if (0 == cell->clientsBuffer[i].connfd) {
      break;
    }
    i++;
  }
  cell->clientsBuffer[i] = conn;
  cell->client_num_current++;

  pthread_mutex_unlock(&mutex);
}

void *conn_thread(void *arg) {
  int cell_index = *(int *)arg;

  if (is_debug() == 1) {
    printf("[debug]:conn_thread,cell_index=%d\r\n", cell_index);
  }

  // 创建epoll去监听client的socket
  int epfd = -1;
  epfd = epoll_create(1024);
  if (-1 == epfd) {
    printf("conn_thread,epoll_create,failed,errno=%d,%s\r\n", errno, strerror(errno));
    exit(0);
  }

  // 通过连接线程池的index把线程拿出来
  reactor *cell = &service.arr1cell[cell_index];

  cell->epfd = epfd;

  struct epoll_event arr1event[1024];
  while (1) {
    pthread_mutex_lock(&mutex);
    if (cell->client_num_current > 0) {
      // 找到client连接缓冲区中未处理的client连接
      for (int i = 0; i < 1024; i++) {
        if (cell->clientsBuffer[i].connfd > 0) {
          // 将未处理的client连接转移到client连接区中的空位
          for (int j = 0; j < 1024; j++) {
            if (cell->clients[j].connfd == 0) {
              cell->clients[j] = cell->clientsBuffer[i];
              epoll_add(cell->epfd, EPOLLIN, cell->clients[j].connfd);
              break;
            }
          }
          // 重置client连接缓冲区中的对应位置
          cell->clientsBuffer[i].connfd = 0;
          cell->client_num_current--;
        }
      }
      // 理论上到这里client_num_current应该正好是0，下面这段防卫代码理论上永远不会执行
      if (cell->client_num_current < 0) {
        cell->client_num_current = 0;
      }
    }
    pthread_mutex_unlock(&mutex);

    // 等待epoll事件
    int rtvl = -1;
    rtvl = epoll_wait(cell->epfd, arr1event, 1024, 1);
    if (-1 == rtvl) {
      if (errno == EINTR) {
        continue;
      } else {
        printf("conn_thread,epoll_wait,failed,errno=%d,%s\r\n", errno, strerror(errno));
        break;
      }
    }
    // rtvl=0时，表示没有事件
    if (rtvl > 0) {
      // 依次处理事件
      for (int i = 0; i < rtvl; i++) {
        int temp_fd = arr1event[i].data.fd;

        // EPOLLOUT放EPOLLIN前面
        if (EPOLLOUT == arr1event[i].events) {
          // EPOLLOUT一般是手动触发的
          connection *conn = connection_find(cell, temp_fd);
          int rtvl = -1;
          rtvl = write_data(conn);
          if (-1 == rtvl) {
            connection_del(cell, conn);
          } else if (0 == rtvl) {
            // 一次发完了，设置回EPOLLIN
            epoll_set(cell->epfd, EPOLLIN, conn->connfd);
          } else if (1 == rtvl) {
            // 还是只发了一半，继续触发EPOLLOUT
            epoll_set(cell->epfd, EPOLLIN | EPOLLOUT, conn->connfd);
          }
        }

        if (EPOLLIN == arr1event[i].events) {
          // 触发EPOLLIN事件，表示有client发送数据过来了
          connection *conn = connection_find(cell, temp_fd);
          if (is_debug() == 1) {
            printf("[debug]:conn_thread,find_connection,connfd=%d\r\n", conn->connfd);
          }
          int recv_bytes = recv_data(conn);
          if (-1 == recv_bytes) {
            connection_del(cell, conn);
          }
          if (recv_bytes > 0) {
            // 收到数据，开始处理，这里直接输出
            printf("conn_thread:recv_data=%s\r\n", conn->recv_buffer);
            // 清理接收缓冲区的内容
            memset(conn->recv_buffer, 0, sizeof(conn->recv_buffer));
            conn->recv_buffer_last = 0;

            char res_data[] = "HTTP/1.1 OK 200\r\nContent-Type: text/html\r\nContent-Length: 12\r\n\r\nhello, world";
            push_data(conn, res_data, strlen(res_data));

            int rtvl = -1;
            rtvl = write_data(conn);
            if (-1 == rtvl) {
              connection_del(cell, conn);
            } else if (1 == rtvl) {
              // 只发了一半的时候需要触发一次EPOLLOUT
              epoll_set(cell->epfd, EPOLLIN | EPOLLOUT, conn->connfd);
            }
          }
        }
      }
    }
  }
}

connection *connection_find(reactor *cell, int connfd) {
  if (0 == connfd) {
    return NULL;
  }
  for (int i = 0; i < 1024; i++) {
    if (connfd == cell->clients[i].connfd) {
      return &cell->clients[i];
    }
  }
  return NULL;
}

void connection_del(reactor *cell, connection *conn) {
  if (is_debug() == 1) {
    printf("[debug]:connection_del,connfd=%d\r\n", conn->connfd);
  }

  memset(conn->recv_buffer, 0, sizeof(conn->recv_buffer));
  conn->recv_buffer_max = 0;
  conn->recv_buffer_last = 0;
  conn->recv_buffer_full = 0;

  memset(conn->send_buffer, 0, sizeof(conn->recv_buffer));
  conn->send_buffer_max = 0;
  conn->send_buffer_last = 0;
  conn->send_buffer_full = 0;

  // 理论上到这里应该只有EPOLLIN，理论上EPOLLOUT应该在循环里就被移除
  epoll_del(cell->epfd, EPOLLIN, conn->connfd);

  // 关闭client的socket句柄
  close(conn->connfd);
  // 重置client连接区中的对应位置
  conn->connfd = 0;
}
