#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>

// The semid_ds data structure is defined in <sys/sem.h> as follows:
// struct semid_ds {
//   struct ipc_perm sem_perm; /* Ownership and permissions */
//   time_t sem_otime;         /* Last semop time */
//   time_t sem_ctime;         /* Creation time/time of last modification via semctl() */
//   unsigned long sem_nsems;  /* No. of semaphores in set */
// };

// 信号量，信号量控制
int main() {
  int semid = semget(0x1000, 1, 0);
  printf("smeid=%d\r\n", semid);
  printf("errno=%d,%s\r\n", errno, strerror(errno));

  // 如果是信号量集合，那么第2个参数可以表示要操作信号量集合中的哪个信号量
  // semctl() performs the control operation specified by cmd on the System V semaphore set identified by semid,
  // or on the semnum-th semaphore of that set.  (The semaphores in a set are numbered starting at 0.)
  // This function has three or four arguments, depending on cmd.
  // When there are four, the fourth has the type union semun. The calling program must define this union as follows:
  union semun {
    int val;               /* Value for SETVAL */
    struct semid_ds *buf;  /* Buffer for IPC_STAT, IPC_SET */
    unsigned short *array; /* Array for GETALL, SETALL */
    struct seminfo *__buf; /* Buffer for IPC_INFO (Linux-specific) */
  };

  union semun buf;
  buf.val = 1; //信号量为1

  // 设置信号量
  // SETVAL
  // Set the semaphore value (semval) to arg.val for the semnum-th semaphore of the set,
  // updating also the sem_ctime member of the semid_ds structure associated with the set.
  // Undo entries are cleared for altered semaphores in all processes.
  // If the changes to semaphore values would permit blocked semop(2) calls in other processes to proceed, then those processes are woken up.
  // The calling process must have alter permission on the semaphore set.
  int res1 = semctl(semid, 0, SETVAL, buf);
  printf("SETVAL res1=%d\r\n", res1);

  // 获取信号量
  // GETVAL
  // Return semval (i.e., the semaphore value) for the semnum-th semaphore of the set.
  // The calling process must have read permission on the semaphore set.
  int res2 = semctl(semid, 0, GETVAL);
  printf("GETVAL res2=%d\r\n", res2);

  // 和消息队列一样也有下面两个参数
  // IPC_STAT
  // Copy information from the kernel data structure associatedwith semid into the semid_ds structure pointed to byarg.buf.
  // The argument semnum is ignored.  The calling process must have read permission on the semaphore set.

  // IPC_RMID
  // Immediately remove the semaphore set, awakening all processes blocked in semop(2) calls on the set (with an error return and errno set to EIDRM).
  // The effective user ID of the calling process must match the creator or owner of the semaphore set, or the caller must be privileged.
  // The argument semnum is ignored.

  return 0;
}