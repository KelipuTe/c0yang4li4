//
// Created by Administrator on 2021/8/9 0009.
//
#include "service.h"
#include <pthread.h>

static pthread_mutex_t  mutex = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
static int stauts=0;

void createThread(void *(*func)(void*),void *arg)
{
    pthread_mutex_lock(&mutex);
    pthread_t tid;
    if(pthread_create(&tid,NULL,func,arg)){
        perror("pthread_create fail");
        exit(0);
    }
    pthread_detach(tid);

    pthread_mutex_unlock(&mutex);
}

void stopListenThread(Service *server)
{
    pthread_mutex_lock(&mutex);

    server->run_flag=0;
    stauts=0;
    while (stauts==0){

        pthread_cond_wait(&cond,&mutex);
    }

    pthread_mutex_unlock(&mutex);
}
void stopConnectThread(reactor *server)
{
    pthread_mutex_lock(&mutex);

    server->run_flag=0;
    stauts=0;
    while (stauts==0){

        pthread_cond_wait(&cond,&mutex);
    }

    pthread_mutex_unlock(&mutex);
}
void notifyThread()
{
    pthread_mutex_lock(&mutex);

    stauts=1;
    pthread_cond_broadcast(&cond);

    pthread_mutex_unlock(&mutex);
}

