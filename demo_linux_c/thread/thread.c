#include <errno.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void *mythread(void *arg) {
  printf("child pthread running\r\n");

  int *j = (int *)arg;
  printf("child pthread,arg=%d\r\n", *j);
  *j = 200;

  // #include <pthread.h>
  // 线程退出，并返回返回值
  pthread_exit((void *)3);
  // 直接return也是可以的
  // return (void *)3;
}

// 多线程编译的时候要加 -lpthread
int main() {
  pthread_t tid1, tid2;

  int x = 100;

  // pthread_create(3)
  // #include <pthread.h>
  // 创建一个线程
  int rtvl1 = pthread_create(&tid1, NULL, mythread, (void *)&x);
  printf("pthread_create(),rtvl1=%d\r\n", rtvl1);
  printf("errno=%d,%s\r\n", errno, strerror(errno));

  int rtvl2 = pthread_create(&tid2, NULL, mythread, (void *)&x);
  printf("pthread_create(),rtvl2=%d\r\n", rtvl2);
  printf("errno=%d,%s\r\n", errno, strerror(errno));

  // pthread_join(3)
  // #include <pthread.h>
  // 子线程合入主线程
  // 主线程调用pthread_join()后，会一直阻塞到子线程结束退出为止
  // 当子线程退出结束后，主线程会继续往后执行
  //   int *status;
  //   pthread_join(tid1, &status);
  //   printf("pthread_join(),tid1=%d,status=%d\r\n", tid1, status);
  //   pthread_join(tid2, &status);
  //   printf("pthread_join(),tid2=%d,status=%d\r\n", tid2, status);

  // pthread_detach(3)
  // #include <pthread.h>
  // 主线程与子线程分离
  // 子线程结束后，资源自动回收
  pthread_detach(tid1);
  pthread_detach(tid2);

  // 如果没有sleep()、pthread_join()、pthread_detach()这些相当于等待的代码结构
  // 主线程执行完pthread_create()后就会结束，子线程没有来得急执行就强制退出了

  printf("x=%d\r\n", x);
  printf("child pthread done\r\n");

  return 0;
}