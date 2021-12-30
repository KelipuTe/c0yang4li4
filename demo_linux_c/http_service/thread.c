#include "service.h"
#include <pthread.h>

static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void create_thread(void *(*func)(void *), void *arg) {
  pthread_mutex_lock(&mutex);

  pthread_t tid;
  int rtvl = -1;
  rtvl = pthread_create(&tid, NULL, func, arg);
  if (is_debug() == 1) {
    printf("[debug]:create_thread,tid=%p\r\n", tid);
  }
  if (rtvl != 0) {
    printf("[error]:create_thread(),pthread_create(),rtvl!=0");
    printf("[error]:errno=%d,errstr%s\r\n", errno, strerror(errno));
    exit(0);
  }
  pthread_detach(tid);

  pthread_mutex_unlock(&mutex);
}