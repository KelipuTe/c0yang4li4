#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>

// 创建信号量
int main() {
  // semget(2)
  // #include <sys/sem.h>
  // 引用一个现存的或者创建一个新的信号量
  // 如果nsems参数大于1，那就是信号量集合
  int semid = semget(0x1000, 1, IPC_CREAT | IPC_EXCL | 0666);
  printf("semget(),smeid=%d\r\n", semid);
  printf("errno=%d,%s\r\n", errno, strerror(errno));

  return 0;
}