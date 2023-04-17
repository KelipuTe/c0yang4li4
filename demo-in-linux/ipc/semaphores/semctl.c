#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <unistd.h>

union semun {
  int val;               /* Value for SETVAL */
  struct semid_ds *buf;  /* Buffer for IPC_STAT, IPC_SET */
  unsigned short *array; /* Array for GETALL, SETALL */
  struct seminfo *__buf; /* Buffer for IPC_INFO (Linux-specific) */
};

// 信号量控制
int main() {
  printf("[debug]:getpid()=%d\n", getpid());

  int semId = semget(0x1000, 1, 0);
  printf("[debug]:semId=%d, errno=%d, error=%s\n", semId, errno, strerror(errno));

  union semun buf;
  buf.val = 3; // 信号量设置为 3

  // int semctl(int semid, int semnum, int cmd, ...);
  // 如果是信号量集合，那么 semnum 参数可以表示要操作信号量集合中的哪个信号量
  // cmd = SETVAL 时，设置信号量
  int semctlResult = semctl(semId, 0, SETVAL, buf);
  printf("[debug]:SETVAL, semctlResult=%d\n", semctlResult);
  // cmd = GETVAL 时，获取信号量
  semctlResult = semctl(semId, 0, GETVAL);
  printf("[debug]:GETVAL, semctlResult=%d\n", semctlResult);

  return 0;
}