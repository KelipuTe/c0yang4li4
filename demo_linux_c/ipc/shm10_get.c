#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/shm.h>

// 共享内存，共享内存创建
int main() {
  // A new shared memory segment, with size equal to the value of size rounded up to a multiple of PAGE_SIZE, is created if key has the value IPC_PRIVATE
  // or key isn't IPC_PRIVATE, no shared memory segment corresponding to key exists, and IPC_CREAT is specified in shmflg.
  // If shmflg specifies both IPC_CREAT and IPC_EXCL and a shared memory segment already exists for key,
  // then shmget() fails with errno set to EEXIST.  (This is analogous to the effect of the combination O_CREAT | O_EXCL for open(2).)

  // 创建一个新的共享内存，返回共享内存id
  //   int shmid = shmget(0x1000, 1024, IPC_CREAT | IPC_EXCL | 0666);

  // 引用一个现存的共享内存，返回共享内存id
  int shmid = shmget(0x1000, 0, 0);

  printf("shmid=%d\r\n", shmid);
  printf("errno=%d,%s\r\n", errno, strerror(errno));

  return 0;
}