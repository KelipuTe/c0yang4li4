#include <errno.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int x = 100;

void *mythread() {
  // 下面这段代码
  // 如果没有互斥锁的保护，结果会输出两次200
  // 两个线程都会读到100，然后阻塞，然后+100，然后赋值回去
  // 如果有互斥锁的保护，两个线程会顺序执行，结果会依次输出200，300

  // pthread_mutex_lock(3p)
  // #include <pthread.h>
  // 加锁，如果加不上就会被阻塞
  pthread_mutex_lock(&mutex);
  printf("child pthread running\r\n");
  int y = x;
  sleep(2);
  y += 100;
  printf("child pthread,y=%d\r\n", y);
  x = y;
  // pthread_mutex_lock(3p)
  // #include <pthread.h>
  // 释放锁
  pthread_mutex_unlock(&mutex);
  pthread_exit((void *)3);
}

// 互斥锁
int main() {
  pthread_t tid1, tid2;

  int rtvl1 = pthread_create(&tid1, NULL, mythread, NULL);
  printf("pthread_create(),rtvl1=%d\r\n", rtvl1);
  printf("errno=%d,%s\r\n", errno, strerror(errno));

  int rtvl2 = pthread_create(&tid2, NULL, mythread, NULL);
  printf("pthread_create(),rtvl2=%d\r\n", rtvl2);
  printf("errno=%d,%s\r\n", errno, strerror(errno));

  int *status;
  pthread_join(tid1, &status);
  printf("pthread_join(),tid1=%d,status=%d\r\n", tid1, status);
  pthread_join(tid2, &status);
  printf("pthread_join(),tid2=%d,status=%d\r\n", tid2, status);

  printf("child pthread done\r\n");

  return 0;
}