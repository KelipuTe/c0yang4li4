#ifndef REACTOR_H
#define REACTOR_H

#include "connection.h"

typedef struct reactor {
  int cell_no;
  int epoll_fd;
  int current_client_num;
  int max_client_num;
  struct connection *clients;
  struct connection *clientsBuffer;

} reactor;

extern void *cell_event_loop(void *arg);
extern void add_connection(reactor *cell, connection client);

#endif