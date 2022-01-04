#ifndef CONNECTION_H
#define CONNECTION_H

#include <netinet/in.h>
#include <stdlib.h>

//接收缓冲区最大长度，1024*1024
#define RECV_BUFFER_MAX 1048576

//发送缓冲区最大长度，1024*1024
#define SEND_BUFFER_MAX 1048576

// 键值对数据结构
typedef struct data_kv {
  char *p1key;
  char *p1value;
} data_kv;

// http报文数据结构
typedef struct http_data {
  char *p1method;
  char *p1uri;
  char *p1version;

  int header_len;
  data_kv *p1header_data;

  int body_len;
  data_kv *p1get_data;
  data_kv *p1post_data;
} http_data;

typedef struct connection {
  int connfd;               //client的socket句柄，accept()返回的那个socket
  char ip[INET_ADDRSTRLEN]; //client的ip
  int port;                 //client的端口号

  char *recv_buffer;    //接收缓冲区
  int recv_buffer_last; //接收缓冲区当前数据的末尾
  int recv_buffer_max;  //接收缓冲区最大长度
  int recv_buffer_full; //接收缓冲区是否已满

  http_data *p1http_data;

  char *send_buffer;    //发送缓冲区
  int send_buffer_last; //发送缓冲区当前数据的末尾
  int send_buffer_max;  //发送缓冲区最大长度
  int send_buffer_full; //发送缓冲区是否已满
} connection;

// 接收client发送过来的数据
// 返回值，-1=异常，0=一次性发送完，1=只发了一半
extern int recv_data(connection *conn);

// 向client发送缓冲区添加响应数据
extern int push_data(connection *conn, char *res_data, int res_data_len);

// 向client发送发送缓冲区中的数据
// 返回值，-1=异常，0=一次性发送完，1=只发了一半
extern int write_data(connection *conn);

// 检查接收缓冲区中的数据是不是完整的http报文
extern int get_http_req_complete(connection *p1conn);

// 解析http报文
extern int parse_http_req(connection *p1conn);

#endif