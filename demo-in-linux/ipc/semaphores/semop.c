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
  buf.val = 10;

  int semctlResult = semctl(semId, 0, SETVAL, buf);
  printf("[debug]:SETVAL, semctlResult=%d\n", semctlResult);
  semctlResult = semctl(semId, 0, GETVAL);
  printf("[debug]:GETVAL, semctlResult=%d\n", semctlResult);

  struct sembuf sbuf;
  sbuf.sem_num = 0; // 操作信号量集合中第 1 个信号量
  sbuf.sem_op = -2; // 增加（正数）或减少（复数）信号量
  sbuf.sem_flg = SEM_UNDO;

  // 对选定的信号量进行操作
  // int semop(int semid, struct sembuf *sops, size_t nsops);
  // #include <sys/sem.h>
  int semopResult = semop(semId, &sbuf, 1);
  printf("[debug]:semopResult=%d\n", semopResult);

  semctlResult = semctl(semId, 0, GETVAL);
  printf("[debug]:GETVAL, semctlResult=%d\n", semctlResult);

  // 当信号量集合中信号量有多个时，可以批量进行操作
  // struct sembuf sbuf[2];
  // 操作信号量集合中第 1 个信号量
  // sbuf[0].sem_num = 0;
  // sbuf[0].sem_op = -2;
  // sbuf[0].sem_flg = SEM_UNDO;
  // 操作信号量集合中第 2 个信号量
  // sbuf[1].sem_num = 0;
  // sbuf[1].sem_op = -2;
  // sbuf[1].sem_flg = SEM_UNDO;
  // 这里的 nsops 参数就是 2 了，表示操作 2 个信号量
  // semopResult = semop(semId, sbuf, 2);

  return 0;
}