#include "service.h"
#include <pthread.h>

static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void create_thread(void *(*func)(void *), void *arg) {
  pthread_mutex_lock(&mutex);
  pthread_t tid;
  int ret = pthread_create(&tid, NULL, func, arg);
  if (ret != 0) {
    printf("pthread_create=%d\r\n", ret);
    perror("pthread_create failed");
    exit(0);
  }
  pthread_detach(tid);

  pthread_mutex_unlock(&mutex);
}