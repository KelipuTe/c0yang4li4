#ifndef EPOLL_H
#define EPOLL_H
extern void event_set(int epoll_fd, int event, int sockfd);
extern void event_del(int epoll_fd, int event, int sockfd);
extern void event_set2(int epoll_fd, int event, int sockfd);
#endif