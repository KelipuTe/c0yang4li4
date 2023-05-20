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
  *j = *j + 100;

  int *status = malloc(sizeof(int));
  if (200 == *((int *)arg)) {
    *status = 2;
    // 线程退出，并返回返回值
    pthread_exit((void *)status);
  } else {
    *status = 3;
    // 直接 return 也是可以的
    return (void *)status;
  }
}

int main() {
  pthread_t tid1, tid2;
  int x1 = 100, x2 = 200;

  // 创建一个线程
  int pthreadCreateResult = pthread_create(&tid1, NULL, mythread, (void *)&x1);
  printf("[debug]:pthread_create(), pthreadCreateResult=%d\n", pthreadCreateResult);
  printf("[debug]:errno=%d, strerror=%s\n", errno, strerror(errno));

  pthreadCreateResult = pthread_create(&tid2, NULL, mythread, (void *)&x2);
  printf("[debug]:pthread_create(), pthreadCreateResult=%d\n", pthreadCreateResult);
  printf("[debug]:errno=%d, strerror=%s\n", errno, strerror(errno));

  // 子线程合入主线程
  int *status1;
  pthread_join(tid1, (void **)&status1);
  printf("[debug]:pthread_join(), tid1=%ld, status=%d\n", (long)tid1, *status1);
  free(status1);

  int *status2;
  pthread_join(tid2, (void **)&status2);
  printf("[debug]:pthread_join(), tid2=%ld, status=%d\n", (long)tid2, *status2);
  free(status2);

  printf("[info]:x1=%d, x2=%d\n", x1, x2);
  printf("[debug]:child pthread done\n");

  return 0;
}