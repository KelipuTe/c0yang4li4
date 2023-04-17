#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>

// 连接共享内存和写入数据
int main() {
  printf("[debug]:getpid()=%d\n", getpid());

  int shmId = shmget(0x1000, 0, 0);
  printf("[debug]:shmId=%d, errno=%d, error=%s\n", shmId, errno, strerror(errno));

  // 连接共享内存
  // void *shmat(int shmid, const void *shmaddr, int shmflg);
  char *msg = (char *)shmat(shmId, NULL, 0);
  // 写入数据，就是操作内存
  memcpy(msg, "hello", 5);

  return 0;
}