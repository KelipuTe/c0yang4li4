#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>

// 信号量，信号量创建
int main() {
  // A new set of nsems semaphores is created if key has the value IPC_PRIVATE
  // or if no existing semaphore set is associated with key and IPC_CREAT is specified in semflg.
  // If semflg specifies both IPC_CREAT and IPC_EXCL and a semaphore set already exists for key,
  // then semget() fails with errno set to EEXIST. (This is analogous to the effect of the combination O_CREAT | O_EXCL for open(2).)

  // 创建一个新的信号量，返回信号量id
  // 如果第2个参数大于1，那就是信号量集合
  //   int semid = semget(0x1000, 1, IPC_CREAT | IPC_EXCL | 0666);

  // 引用一个现存的信号量，返回信号量id
  int semid = semget(0x1000, 1, 0);

  printf("smeid=%d\r\n", semid);
  printf("errno=%d,%s\r\n", errno, strerror(errno));

  return 0;
}