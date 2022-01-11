#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/shm.h>

// 创建共享内存
int main() {
  // shmget(2)
  // #include <sys/shm.h>
  // 引用一个现存的或者创建一个新的共享内存
  int shmid = shmget(0x1000, 1024, IPC_CREAT | IPC_EXCL | 0666);
  printf("shmget(),shmid=%d\r\n", shmid);
  printf("errno=%d,%s\r\n", errno, strerror(errno));

  return 0;
}