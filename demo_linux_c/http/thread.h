//
// Created by Administrator on 2021/8/9 0009.
//

#ifndef CLESSON_THREAD_H
#define CLESSON_THREAD_H
#include "service.h"
extern void createThread(void *(*func)(void*),void *arg);
extern void stopListenThread(Service *server);
extern void notifyThread();
extern void stopConnectThread(reactor *server);
#endif //CLESSON_THREAD_H
