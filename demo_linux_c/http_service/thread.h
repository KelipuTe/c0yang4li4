#ifndef THREAD_H
#define THREAD_H

// 创建线程
extern void create_thread(void *(*func)(void *), void *arg);

#endif