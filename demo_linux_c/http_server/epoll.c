#include "service.h"

void event_set(int event, int sockfd) {

  struct epoll_event event1;
  event1.events = event;
  event1.data.fd = sockfd;

  int ret_val = epoll_ctl(service1.epoll_fd, EPOLL_CTL_ADD, sockfd, &event1);
  if (ret_val != 0) {
    perror("event_set fail");
  }
}

void event_del(int event, int sockfd) {
  struct epoll_event event1;
  event1.events = event;
  event1.data.fd = sockfd;

  int ret_val = epoll_ctl(service1.epoll_fd, EPOLL_CTL_DEL, sockfd, &event1);
  if (ret_val != 0) {
    perror("event_del fail");
  }
}