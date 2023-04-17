#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <unistd.h>

// 创建信号量
int main() {
  printf("[debug]:getpid()=%d\n", getpid());

  // 创建一个新的或者引用一个现存的信号量
  // int semget(key_t key, int nsems, int semflg);
  // 如果 nsems 参数大于 1，那就是信号量集合
  int semId = semget(0x1000, 1, IPC_CREAT | IPC_EXCL | 0666);
  printf("[debug]:semId=%d, errno=%d, error=%s\n", semId, errno, strerror(errno));

  return 0;
}