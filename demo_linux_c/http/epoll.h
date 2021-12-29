//
// Created by Administrator on 2021/8/9 0009.
//

#ifndef CLESSON_EPOLL_H
#define CLESSON_EPOLL_H

#include "service.h"
#define MAX_CONNECTIONS 1024

extern void eventAdd(int epfd,int event,int sockfd);
extern void eventDel(int epfd,int event,int sockfd);
extern void eventSet(int epfd,int event,int sockfd);
#endif //CLESSON_EPOLL_H
