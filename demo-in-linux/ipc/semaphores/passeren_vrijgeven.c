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
  struct sembuf sbuf;
  sbuf.sem_num = 0;
  sbuf.sem_op = sv;
  sbuf.sem_flg = SEM_UNDO;
  semop(semid, &sbuf, 1);
}

// 信号量 pv 操作，p 表示信号量 -1，v 表示信号量 +1
int main() {
  printf("[debug]:parent, getpid()=%d\n", getpid());
  semid = semget(0x1000, 1, 0);

  // 设置信号量为1
  union semun buf;
  buf.val = 1;
  int ret = semctl(semid, 0, SETVAL, buf);

  // 子进程和父进程都要去对信号量执行 -1 操作，但是信号量只有 1
  // 所以当父进程执行过 -1 操作之后，子进程想再 -1 时就会被阻塞
  // 直到父进程执行 +1 操作之后，信号量大于 0 时，子进程才能继续执行 -1 操作

  pid_t pid = fork();
  if (pid == 0) {
    pv(-1);
    printf("[debug]:child, getpid()=%d\n", getpid());
    sleep(2);
    pv(1);

    return 0;
  }

  pv(-1);
  printf("[debug]:parent, getpid()=%d\n", getpid());
  sleep(2);
  pv(1);

  wait(0);
  printf("[debug]:parent, finish\n");

  return 0;
}