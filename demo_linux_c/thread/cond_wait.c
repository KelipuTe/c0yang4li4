#include <errno.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

int status = 0;

void *mythread1(void *arg) {
  pthread_mutex_lock(&mutex);
  printf("child pthread running\r\n");
  int *j = (int *)arg;
  printf("child pthread,arg=%d\r\n", *j);
  while (0 == status) {
    // pthread_cond_wait(3p)
    // #include <pthread.h>
    // 调用pthread_cond_wait()会阻塞当前线程，并且会释放互斥锁
    // 当pthread_cond_wait()被激活之后会再自动加锁
    pthread_cond_wait(&cond, &mutex);
  }
  printf("child pthread,arg=%d\r\n", *j);
  pthread_mutex_unlock(&mutex);
  pthread_exit((void *)3);
}

void *mythread2(void *arg) {
  pthread_mutex_lock(&mutex);
  printf("child pthread running\r\n");
  int *j = (int *)arg;
  printf("child pthread,arg=%d\r\n", *j);

  sleep(2);
  status = 1;

  // pthread_cond_signal(3p)
  // #include <pthread.h>
  // 把阻塞的线程唤醒，唤醒一条
  // pthread_cond_signal(&cond);

  // pthread_cond_signal(3p)
  // #include <pthread.h>
  // 把阻塞的线程唤醒，唤醒全部
  pthread_cond_broadcast(&cond);

  printf("child pthread,arg=%d\r\n", *j);
  pthread_mutex_unlock(&mutex);
  pthread_exit((void *)3);
}

// 条件变量
int main() {
  pthread_t tid1, tid2, tid3;

  int x1 = 1;
  int rtvl1 = pthread_create(&tid1, NULL, mythread1, (void *)&x1);
  printf("pthread_create(),rtvl1=%d\r\n", rtvl1);
  printf("errno=%d,%s\r\n", errno, strerror(errno));

  int x2 = 2;
  int rtvl2 = pthread_create(&tid2, NULL, mythread1, (void *)&x2);
  printf("pthread_create(),rtvl2=%d\r\n", rtvl2);
  printf("errno=%d,%s\r\n", errno, strerror(errno));

  int x3 = 3;
  int rtvl3 = pthread_create(&tid3, NULL, mythread2, (void *)&x3);
  printf("pthread_create(),rtvl3=%d\r\n", rtvl3);
  printf("errno=%d,%s\r\n", errno, strerror(errno));

  int *status;
  pthread_join(tid1, &status);
  printf("pthread_join(),tid1=%d,status=%d\r\n", tid1, status);
  pthread_join(tid2, &status);
  printf("pthread_join(),tid2=%d,status=%d\r\n", tid2, status);
  pthread_join(tid3, &status);
  printf("pthread_join(),tid3=%d,status=%d\r\n", tid3, status);

  printf("child pthread done\r\n");

  return 0;
}