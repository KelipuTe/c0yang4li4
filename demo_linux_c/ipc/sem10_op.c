#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>

// 信号量，信号量控制
int main() {
  //   int semid = semget(0x1000, 1, IPC_CREAT | IPC_EXCL | 0666);
  int semid = semget(0x1000, 1, 0);
  printf("smeid=%d\r\n", semid);
  printf("errno=%d,%s\r\n", errno, strerror(errno));

  union semun {
    int val;               /* Value for SETVAL */
    struct semid_ds *buf;  /* Buffer for IPC_STAT, IPC_SET */
    unsigned short *array; /* Array for GETALL, SETALL */
    struct seminfo *__buf; /* Buffer for IPC_INFO (Linux-specific) */
  };

  union semun buf;
  buf.val = 10;

  int res1 = semctl(semid, 0, SETVAL, buf);
  printf("SETVAL res1=%d\r\n", res1);

  int res2 = semctl(semid, 0, GETVAL);
  printf("GETVAL res2=%d\r\n", res2);

  // semop() performs operations on selected semaphores in the set indicated by semid.
  // Each of the nsops elements in the array pointed to by sops is a structure that specifies an operation to be performed on a single semaphore.
  // The elements of this structure are of type struct sembuf, containing the following members:
  // unsigned short sem_num;  /* semaphore number */
  // short          sem_op;   /* semaphore operation */
  // short          sem_flg;  /* operation flags */
  // Flags recognized in sem_flg are IPC_NOWAIT and SEM_UNDO.
  // If an operation specifies SEM_UNDO, it will be automatically undone when the process terminates.

  struct sembuf sbuf;
  sbuf.sem_num = 0; //操作信号集中第1个信号量
  sbuf.sem_op = -2; //增加或减少信号量
  sbuf.sem_flg = SEM_UNDO;

  int res3 = semop(semid, &sbuf, 1);
  printf("semop res3=%d\r\n", res3);

  int res4 = semctl(semid, 0, GETVAL);
  printf("GETVAL res4=%d\r\n", res4);

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
  // 这里的第3个参数就是2了，表示操作2个
  // int res3 = semop(semid, sbuf, 2);

  return 0;
}