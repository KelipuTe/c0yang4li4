#include "service.h"
#include <pthread.h>

static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void create_thread(void *(*func)(void *), void *arg) {
  pthread_mutex_lock(&mutex);

  pthread_t tid;
  int rtvl = -1;
  rtvl = pthread_create(&tid, NULL, func, arg);
  if (rtvl != 0) {
    printf("pthread_create failed,rtvl=%d,errno=%d,%s\r\n", rtvl, errno, strerror(errno));
    exit(0);
  }
  pthread_detach(tid);

  pthread_mutex_unlock(&mutex);
}