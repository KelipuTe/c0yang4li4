#ifndef EPOLL_H
#define EPOLL_H
extern void event_set(int event, int sockfd);
extern void event_del(int event, int sockfd);
#endif