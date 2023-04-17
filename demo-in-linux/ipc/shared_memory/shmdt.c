#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>

// 共享内存，共享内存连接和断开
int main() {
  int shmid = shmget(0x1000, 0, 0);
  printf("shmget(),shmid==%d\r\n", shmid);
  printf("errno=%d,%s\r\n", errno, strerror(errno));

  // 共享内存连接
  char *msg = (char *)shmat(shmid, NULL, 0);
  // 数据就在内存里，可以直接操作
  printf("msg=%s\r\n", msg);
  // shmdt(2)
  // #include <sys/shm.h>
  // 共享内存连接断开
  int rtvl1 = shmdt((void *)msg);
  printf("shmdt(),rtvl1=%d\r\n", rtvl1);

  return 0;
}