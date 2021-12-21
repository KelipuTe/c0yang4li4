#ifndef CONNECTION_H
#define CONNECTION_H

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
} connection;

#endif