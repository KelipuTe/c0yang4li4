#ifndef CONNECTION_H
#define CONNECTION_H

#include <netinet/in.h>

typedef struct connection {
  int sockfd;
  int port;
  char ip[INET_ADDRSTRLEN];

  char *recv_buffer;
  char *send_buffer;
  int recv_max_bytes;
  int send_max_bytes;
  int recv_last;
  int send_last;

  int recv_buffer_full;
  int send_buffer_full;
} connection;

extern int recv_data(connection *client);
extern int push_data(connection *client, char *data, int len);
extern int write_data(connection *client);
#endif