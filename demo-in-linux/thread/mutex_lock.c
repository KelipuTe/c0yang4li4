#include <errno.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// 初始化锁
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int x = 100;

void *mythread() {
  printf("[debug]:child pthread running\r\n");

  // 加锁，如果加不上就会被阻塞
  pthread_mutex_lock(&mutex);
  int y = x;
  sleep(1);
  y = y + 100;
  x = y;
  printf("[info]:child pthread, y=%d\n", x);
  // 释放锁
  pthread_mutex_unlock(&mutex);

  int *status = malloc(sizeof(int));
  *status = 3;
  pthread_exit((void *)status);
}

// 互斥锁
int main() {
  pthread_t tid1, tid2;

  int pthreadCreateResult = pthread_create(&tid1, NULL, mythread, NULL);
  printf("[debug]:pthread_create(), pthreadCreateResult=%d\n", pthreadCreateResult);
  printf("[debug]:errno=%d, strerror=%s\n", errno, strerror(errno));

  pthreadCreateResult = pthread_create(&tid2, NULL, mythread, NULL);
  printf("[debug]:pthread_create(), pthreadCreateResult=%d\n", pthreadCreateResult);
  printf("[debug]:errno=%d, strerror=%s\n", errno, strerror(errno));

  int *status1;
  pthread_join(tid1, (void **)&status1);
  printf("[debug]:pthread_join(), tid1=%ld, status=%d\n", (long)tid1, *status1);
  free(status1);

  int *status2;
  pthread_join(tid2, (void **)&status2);
  printf("[debug]:pthread_join(), tid2=%ld, status=%d\n", (long)tid2, *status2);
  free(status2);

  printf("[debug]:child pthread done\n");

  return 0;
}