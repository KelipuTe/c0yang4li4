#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/shm.h>
#include <unistd.h>

// 创建共享内存
int main() {
  printf("[debug]:getpid()=%d\n", getpid());

  // 创建一个新的或者引用一个现存的共享内存
  // int shmget(key_t key, size_t size, int shmflg);
  int shmId = shmget(0x1000, 1024, IPC_CREAT | IPC_EXCL | 0666);
  printf("[debug]:shmId=%d, errno=%d, error=%s\n", shmId, errno, strerror(errno));

  return 0;
}