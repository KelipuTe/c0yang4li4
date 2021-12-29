#ifndef SERVICE_H
#define SERVICE_H

#include "connection.h"
#include "reactor.h"
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

typedef struct http_service {
  int app_debug; //debug模式，1=开启

  int sockfd;               //service的socket句柄
  char ip[INET_ADDRSTRLEN]; //ip，bind()的sockaddr参数
  int port;                 //端口号，bind()的sockaddr参数
  int backlog;              //最大监听数，listen()的backlog参数

  int thread_num; //连接线程的数量
  int call_num;   //http服务被访问的次数，用于线程池轮询调度

  int epfd; //监听service的socket的epoll句柄

  reactor *arr1cell; //连接线程池

  void (*socket_init)(void);
  void (*socket_bind_addr)(void);
  void (*socket_listen)(void);
  void (*service_start)(void);
} http_service;

extern http_service service;

// 是不是debug模式，1=开启
extern int is_debug();
// socket初始化
extern void socket_init();
// 将地址分配给socket
extern void socket_bind_addr();
// socket开启监听
extern void socket_listen();
// 启动1个线程监听socket，启动thread_num个线程连接socket
extern void service_start();

#endif