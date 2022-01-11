#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>

union semun {
  int val;               /* Value for SETVAL */
  struct semid_ds *buf;  /* Buffer for IPC_STAT, IPC_SET */
  unsigned short *array; /* Array for GETALL, SETALL */
  struct seminfo *__buf; /* Buffer for IPC_INFO (Linux-specific) */
};

// 信号量控制
int main() {
  int semid = semget(0x1000, 1, 0);
  printf("semget(),smeid=%d\r\n", semid);
  printf("errno=%d,%s\r\n", errno, strerror(errno));

  union semun buf;
  buf.val = 10;

  int rtvl1 = semctl(semid, 0, SETVAL, buf);
  printf("semctl(),SETVAL,rtvl1=%d\r\n", rtvl1);
  int rtvl2 = semctl(semid, 0, GETVAL);
  printf("semctl(),GETVAL,rtvl2=%d\r\n", rtvl2);

  struct sembuf sbuf;
  sbuf.sem_num = 0; //操作信号集中第1个信号量
  sbuf.sem_op = -2; //增加或减少信号量
  sbuf.sem_flg = SEM_UNDO;

  // semop(2)
  // #include <sys/sem.h>
  int rtvl3 = semop(semid, &sbuf, 1);
  printf("semop(),rtvl3=%d\r\n", rtvl3);

  int rtvl4 = semctl(semid, 0, GETVAL);
  printf("semctl(),GETVAL,rtvl4=%d\r\n", rtvl4);

  // 当信号集中信号量有多个时
  // 操作信号量可以批量操作
  // struct sembuf sbuf[2];
  // 操作信号集中第1个信号量
  // sbuf[0].sem_num = 0;
  // sbuf[0].sem_op = -2;
  // sbuf[0].sem_flg = SEM_UNDO;
  // 操作信号集中第2个信号量
  // sbuf[1].sem_num = 0;
  // sbuf[1].sem_op = -2;
  // sbuf[1].sem_flg = SEM_UNDO;
  // 这里的nsops参数就是2了，表示操作2个信号量
  // int res3 = semop(semid, sbuf, 2);

  return 0;
}