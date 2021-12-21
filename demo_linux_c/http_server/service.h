#ifndef SERVICE_H
#define SERVICE_H

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

#include "connection.h"
#include "reactor.h"

typedef struct service {
  int call_num;
  int sockfd;
  int port;
  char ip[INET_ADDRSTRLEN];
  int backlog;
  int thread_num;
  int epoll_fd;
  reactor *cell;

  void (*my_init_socket)(void);
  void (*my_bind)(void);
  void (*my_listen)(void);
  void (*my_run)(void);
} service;

extern service service1;
extern void my_init_socket();
extern void my_bind();
extern void my_listen();
extern void my_run();

#endif