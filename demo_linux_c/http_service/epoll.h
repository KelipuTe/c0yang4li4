#ifndef EPOLL_H
#define EPOLL_H

extern void epoll_add(int epfd, int op, int sockfd);

extern void epoll_set(int epfd, int op, int sockfd);

extern void epoll_del(int epfd, int op, int sockfd);

#endif