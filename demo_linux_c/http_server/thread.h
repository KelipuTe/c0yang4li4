#ifndef THREAD_H
#define THREAD_H

extern void create_thread(void *(*func)(void *), void *arg);

#endif