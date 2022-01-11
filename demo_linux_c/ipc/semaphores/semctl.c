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
  buf.val = 1; //信号量设置为1

  // semctl(2)
  // #include <sys/sem.h>
  // 如果是信号量集合，那么semnum参数可以表示要操作信号量集合中的哪个信号量
  // cmd=SETVAL时，设置信号量
  int rtvl1 = semctl(semid, 0, SETVAL, buf);
  printf("semctl(),SETVAL,rtvl1=%d\r\n", rtvl1);
  // cmd=GETVAL时，获取信号量
  int rtvl2 = semctl(semid, 0, GETVAL);
  printf("semctl(),GETVAL,rtvl2=%d\r\n", rtvl2);

  // 和消息队列一样也有IPC_STAT、IPC_RMID这两个参数

  return 0;
}