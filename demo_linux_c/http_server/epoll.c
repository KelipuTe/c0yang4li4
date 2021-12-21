#include "service.h"

void event_set(int epoll_fd, int event, int sockfd) {

  struct epoll_event event1;
  event1.events = event;
  event1.data.fd = sockfd;

  int ret_val = epoll_ctl(epoll_fd, EPOLL_CTL_ADD, sockfd, &event1);
  if (ret_val != 0) {
    perror("event_set fail");
  }
}

void event_del(int epoll_fd, int event, int sockfd) {
  struct epoll_event event1;
  event1.events = event;
  event1.data.fd = sockfd;

  int ret_val = epoll_ctl(epoll_fd, EPOLL_CTL_DEL, sockfd, &event1);
  if (ret_val != 0) {
    perror("event_del fail");
  }
}