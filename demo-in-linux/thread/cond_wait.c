#include <errno.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
// 初始化条件变量
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
// 条件的状态
int condStatus = 0;

void *mythread1(void *arg) {
  printf("[debug]:child pthread1 running\n");

  pthread_mutex_lock(&mutex);
  int *j = (int *)arg;
  printf("[debug]:child pthread1, arg=%d\n", *j);
  while (0 == condStatus) {
    // 调用 pthread_cond_wait() 会阻塞当前线程，并且会释放互斥锁
    // 当 pthread_cond_wait() 被激活之后会再自动加锁
    pthread_cond_wait(&cond, &mutex);
  }
  printf("[debug]:child pthread1, arg=%d\n", *j);
  pthread_mutex_unlock(&mutex);

  int *status = malloc(sizeof(int));
  *status = 2;
  pthread_exit((void *)status);
}

void *mythread2(void *arg) {
  printf("[debug]:child pthread2 running\n");

  pthread_mutex_lock(&mutex);
  int *j = (int *)arg;
  printf("[debug]:child pthread2, arg=%d\n", *j);

  sleep(1);
  condStatus = 1;

  // 唤醒一条阻塞的线程
  // pthread_cond_signal(&cond);
  // 唤醒全部阻塞的线程
  pthread_cond_broadcast(&cond);

  printf("[debug]:child pthread2, arg=%d\n", *j);
  pthread_mutex_unlock(&mutex);

  int *status = malloc(sizeof(int));
  *status = 3;
  pthread_exit((void *)status);
}

// 条件变量
int main() {
  pthread_t tid1, tid2, tid3;
  int x1 = 1, x2 = 2, x3 = 3;

  int pthreadCreateResult = pthread_create(&tid1, NULL, mythread1, (void *)&x1);
  printf("[debug]:pthread_create(), pthreadCreateResult=%d\n", pthreadCreateResult);
  printf("[debug]:errno=%d, strerror=%s\n", errno, strerror(errno));

  pthreadCreateResult = pthread_create(&tid2, NULL, mythread1, (void *)&x2);
  printf("[debug]:pthread_create(), pthreadCreateResult=%d\n", pthreadCreateResult);
  printf("[debug]:errno=%d, strerror=%s\n", errno, strerror(errno));

  pthreadCreateResult = pthread_create(&tid3, NULL, mythread2, (void *)&x3);
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

  int *status3;
  pthread_join(tid3, (void **)&status3);
  printf("[debug]:pthread_join(), tid3=%ld, status=%d\n", (long)tid3, *status3);
  free(status3);

  printf("[debug]:child pthread done\n");

  return 0;
}