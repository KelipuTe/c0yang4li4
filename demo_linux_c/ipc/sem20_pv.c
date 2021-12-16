#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int semid;

union semun {
  int val;               /* Value for SETVAL */
  struct semid_ds *buf;  /* Buffer for IPC_STAT, IPC_SET */
  unsigned short *array; /* Array for GETALL, SETALL */
  struct seminfo *__buf; /* Buffer for IPC_INFO (Linux-specific) */
};

void pv(int sv) {
  struct sembuf sb;
  sb.sem_num = 0;
  sb.sem_op = sv;
  sb.sem_flg = SEM_UNDO;
  semop(semid, &sb, 1);
}
int main() {
  semid = semget(0x1000, 1, 0);

  // 设置信号量为1
  union semun buf;
  buf.val = 1;
  int ret = semctl(semid, 0, SETVAL, buf);

  // 子进程和父进程都要去对信号量执行-1操作，但是信号量只有1
  // 所以当父进程执行过-1操作之后，子进程想再-1时就会被阻塞
  // 直到父进程执行+1操作之后，信号量大于0时，子进程才能继续执行-1操作

  pid_t pid = fork();
  if (pid == 0) {
    pv(-1);
    printf("child,pid=%d\r\n", getpid());
    sleep(3);
    pv(1);

    return 0;
  }

  pv(-1);
  printf("parent,pid=%d\r\n", getpid());
  sleep(3);
  pv(1);

  wait(0);
  printf("parent,finish\r\n");

  return 0;
}