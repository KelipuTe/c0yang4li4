#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>

// 共享内存连接和写入
int main() {
  int shmid = shmget(0x1000, 0, 0);
  printf("shmget(),shmid==%d\r\n", shmid);
  printf("errno=%d,%s\r\n", errno, strerror(errno));

  // shmat(2)
  // #include <sys/shm.h>
  // 共享内存连接
  char *msg = (char *)shmat(shmid, NULL, 0);
  // 写入数据，就是操作内存
  memcpy(msg, "hello", 5);

  return 0;
}