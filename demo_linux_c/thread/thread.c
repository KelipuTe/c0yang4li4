//
// Created by Administrator on 2021/8/7 0007.
//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <pthread.h>
#include <unistd.h>

void *mythread(void *arg){

    printf("i am child thread\r\n");


    int *j =  (int*)arg;
    printf("arg=%d\r\n",*j);
    *j=200;

    //return (void*)2;
    pthread_exit((void*)3);
}
int main()
{

    pthread_t tid,tid2;

    //1 执行完这个语句，主线程执行return结束 整个，新子线程都没有来得急执行就被强制退出了
    //2 子线程根本没有来得急执行，整个进程已经结束
    //pthread_create(&tid,NULL,mythread,(void*)("china"));
    int x = 100;
    pthread_create(&tid,NULL,mythread,(void*)&x);
    pthread_create(&tid2,NULL,mythread,(void*)&x);

    //此时主线程会等待2秒钟，此时cpu会切换到子线程执行【因为我的cpu核数就1核】
    //并行
    //当线程数量<=cpu核心数时，此时是并行执行
    //执行时，可以做到每个核心数运行一个线程

    //并发
    //当线程数量超出核心数量时，此时线程的执行就是并发【每个线程执行一个时间片，然后再切换到其它线程执行】

    //sleep(2);

    //主线程调用 它，会一直阻塞到子线程结束退出为止，否则会一等阻塞
    //当子线程退出结束后，主线程会继续往后执行
    int *status;
    pthread_join(tid,&status);
    pthread_join(tid2,&status);
    //pthread_detach(tid);
    //pthread_detach(tid2);
    printf("x=%d\r\n",x);
    printf("exit child pthread,exit\r\n");

    return 0;
}