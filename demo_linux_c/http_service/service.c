#include "service.h"
#include "connection.h"
#include "epoll.h"
#include "reactor.h"
#include "thread.h"

// 监听线程的处理函数
void *listen_thread();

// 处理socket连接
void socket_accept();

int is_debug() {
  if (1 == service.app_debug) {
    return 1;
  } else {
    return 0;
  }
}

void socket_init() {
  int sockfd = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, 0);
  if (is_debug() == 1) {
    printf("[debug]:socket_init(),socket(),sockfd=%d\r\n", sockfd);
  }
  if (sockfd < 0) {
    printf("[error]:socket_init(),socket(),sockfd<0\r\n");
    printf("[error]:errno=%d,errstr%s\r\n", errno, strerror(errno));
    exit(0);
  }
  service.sockfd = sockfd;

  // 设置socket参数
  int rtvl1 = -1;
  int optval = 1;
  rtvl1 = setsockopt(service.sockfd, SOL_SOCKET, SO_REUSEPORT, &optval, sizeof(optval));
  if (is_debug() == 1) {
    printf("[debug]:socket_init(),setsockopt(),rtvl1=%d\r\n", rtvl1);
  }
  if (-1 == rtvl1) {
    printf("[error]:socket_init(),setsockopt(),-1==rtvl1\r\n");
    printf("[error]:errno=%d,errstr%s\r\n", errno, strerror(errno));
    exit(0);
  }
}

void socket_bind_addr() {
  struct sockaddr_in service_addr;
  service_addr.sin_family = AF_INET;
  service_addr.sin_addr.s_addr = inet_addr(service.ip);
  service_addr.sin_port = htons(service.port);

  int rtvl2 = -1;
  rtvl2 = bind(service.sockfd, (struct sockaddr *)&service_addr, sizeof(service_addr));
  if (-1 == rtvl2) {
    printf("[error]:socket_bind_addr(),bind(),-1==rtvl2");
    printf("[error]:errno=%d,errstr%s\r\n", errno, strerror(errno));
    exit(0);
  }
}

void socket_listen() {
  int rtvl1 = -1;
  rtvl1 = listen(service.sockfd, service.backlog);
  if (-1 == rtvl1) {
    printf("[error]:socket_listen(),listen(),-1==rtvl1");
    printf("[error]:errno=%d,errstr%s\r\n", errno, strerror(errno));
    exit(0);
  }
}

void service_start() {
  // 启动监听线程
  create_thread(listen_thread, NULL);
  // 初始化连接线程池
  service.arr1cell = (reactor *)malloc(sizeof(reactor) * service.thread_num);
  // 启动连接线程
  for (int i = 0; i < service.thread_num; i++) {
    service.arr1cell[i].cell_index = i;
    service.arr1cell[i].client_num_current = 0;
    service.arr1cell[i].client_num_max = CLIENT_MAX_NUM;
    service.arr1cell[i].clients = (connection *)malloc(sizeof(connection) * CLIENT_MAX_NUM);
    service.arr1cell[i].clientsBuffer = (connection *)malloc(sizeof(connection) * CLIENT_MAX_NUM);
    create_thread(conn_thread, &service.arr1cell[i].cell_index);
  }
}

void *listen_thread() {
  // 创建epoll去监听service的socket
  int epfd = -1;
  epfd = epoll_create(CLIENT_MAX_NUM);
  if (-1 == epfd) {
    printf("[error]:listen_thread(),epoll_create(),-1==epfd");
    printf("[error]:errno=%d,errstr%s\r\n", errno, strerror(errno));
    exit(0);
  }
  service.epfd = epfd;
  epoll_add(service.epfd, EPOLLIN, service.sockfd);

  struct epoll_event arr1event[CLIENT_MAX_NUM];
  while (1) {
    // 等待epoll事件
    int rtvl = -1;
    rtvl = epoll_wait(epfd, arr1event, CLIENT_MAX_NUM, EPOLL_WAIT_TIME);
    if (-1 == rtvl) {
      if (errno == EINTR) {
        continue;
      } else {
        printf("[error]:listen_thread(),epoll_wait(),-1==rtvl,errno!=EINTR");
        printf("[error]:errno=%d,errstr%s\r\n", errno, strerror(errno));
        break;
      }
    }
    // rtvl=0时，表示没有事件
    if (rtvl > 0) {
      // 依次处理事件
      if (is_debug() == 1) {
        printf("[debug]:listen_thread(),epoll_wait(),rtvl>0,rtvl=%d\r\n", rtvl);
      }
      for (int i = 0; i < rtvl; i++) {
        int temp_fd = arr1event[i].data.fd;
        if (EPOLLIN == arr1event[i].events && temp_fd == service.sockfd) {
          // 触发EPOLLIN事件，而且是service.sockfd上的，表示有client连接过来了
          socket_accept();
        }
      }
    }
  }
}

void socket_accept() {
  struct sockaddr_in client_addr;
  socklen_t client_addr_len = sizeof(client_addr);

  int connfd = -1;
  connfd = accept(service.sockfd, (struct sockaddr *)&client_addr, &client_addr_len);
  if (is_debug() == 1) {
    printf("[debug]:socket_accept(),accept(),connfd=%d,ip=%s,port=%d\r\n",
           connfd, inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
  }
  if (-1 == connfd) {
    printf("[error]:socket_accept(),accept(),-1==connfd");
    printf("[error]:errno=%d,errstr%s\r\n", errno, strerror(errno));
    exit(0);
  }

  // client连接上之后，服务总请求次数+1
  service.call_num++;
  if (is_debug() == 1) {
    printf("[debug]:socket_accept(),service.call_num=%d\r\n", service.call_num);
  }
  // 计算让连接线程池中哪个连接线程来处理
  int temp_thread_index = service.call_num % service.thread_num;
  if (is_debug() == 1) {
    printf("[debug]:socket_accept(),temp_thread_index=%d\r\n", temp_thread_index);
  }
  reactor *cell = &service.arr1cell[temp_thread_index];
  // 把这个client连接封装一下
  struct connection conn;
  conn.connfd = connfd;
  strcpy(conn.ip, inet_ntoa(client_addr.sin_addr));
  conn.port = ntohs(client_addr.sin_port);
  conn.recv_buffer = (char *)malloc(sizeof(char) * RECV_BUFFER_MAX);
  conn.recv_buffer_max = RECV_BUFFER_MAX;
  conn.recv_buffer_last = 0;
  conn.recv_buffer_full = 0;
  conn.send_buffer = (char *)malloc(sizeof(char) * SEND_BUFFER_MAX);
  conn.send_buffer_max = SEND_BUFFER_MAX;
  conn.send_buffer_last = 0;
  conn.send_buffer_full = 0;
  // 然后丢给这个连接线程处理
  connection_add(cell, conn);
}
