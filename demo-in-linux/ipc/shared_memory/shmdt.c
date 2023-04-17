#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>

// 连接共享内存和断开共享内存
int main() {
  printf("[debug]:getpid()=%d\n", getpid());

  int shmId = shmget(0x1000, 0, 0);
  printf("[debug]:shmId=%d, errno=%d, error=%s\n", shmId, errno, strerror(errno));

  // 连接共享内存
  char *msg = (char *)shmat(shmId, NULL, 0);
  // 数据就在内存里，可以直接操作
  printf("[info]:msg=%s\n", msg);

  // 断开共享内存
  // int shmdt(const void *shmaddr);
  int shmdtResult = shmdt((void *)msg);
  printf("[debug]:shmdtResult=%d\n", shmdtResult);

  return 0;
}