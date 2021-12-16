#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>

// 共享内存，共享内存连接和写入
int main() {
  int shmid = shmget(0x1000, 0, 0);
  printf("shmid=%d\r\n", shmid);
  printf("errno=%d,%s\r\n", errno, strerror(errno));

  // 共享内存连接
  // shmat() attaches the System V shared memory segment identified by shmid to the address space of the calling process.
  char *msg = (char *)shmat(shmid, NULL, 0);
  printf("msg=%s\r\n", msg);
  // 写入数据
  memcpy(msg, "hello", 5);

  return 0;
}