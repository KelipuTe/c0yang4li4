#include <errno.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void *mythread(void *arg) {
  printf("[debug]:child pthread running\n");

  int *j = (int *)arg;
  printf("[info]:child pthread, arg=%d\n", *j);
  *j = *j + 200;

  // 线程退出，并返回返回值
  pthread_exit((void *)3);
}

int main() {
  pthread_t tid1, tid2;
  int x = 100;

  // 创建一个线程
  int pthreadCreateResult = pthread_create(&tid1, NULL, mythread, (void *)&x);
  printf("[debug]:pthread_create(), pthreadCreateResult=%d\n", pthreadCreateResult);
  printf("[debug]:errno=%d, strerror=%s\n", errno, strerror(errno));

  pthreadCreateResult = pthread_create(&tid2, NULL, mythread, (void *)&x);
  printf("[debug]:pthread_create(), pthreadCreateResult=%d\n", pthreadCreateResult);
  printf("[debug]:errno=%d, strerror=%s\n", errno, strerror(errno));

  // 主线程与子线程分离
  pthread_detach(tid1);
  pthread_detach(tid2);

  sleep(1);

  printf("[info]:x=%d\n", x);
  printf("[debug]:child pthread done\n");

  return 0;
}