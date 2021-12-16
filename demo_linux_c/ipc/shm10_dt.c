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
  printf("shmid=%d\r\n", shmid);
  printf("errno=%d,%s\r\n", errno, strerror(errno));

  // 共享内存连接
  char *msg = (char *)shmat(shmid, NULL, 0);
  printf("msg=%s\r\n", msg);

  // 共享内存连接断开
  // shmdt() detaches the shared memory segment located at the address specified by shmaddr from the address space of the calling process.
  // The to-be-detached segment must be currently attached with shmaddr equal to the value returned by the attaching shmat() call.
  int res = shmdt((void *)msg);
  printf("shmdt ret=%d\r\n", res);
  return 0;
}