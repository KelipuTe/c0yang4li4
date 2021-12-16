#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>

// The msqid_ds data structure is defined in<sys / msg.h> as follows :
// struct msqid_ds {
//   struct ipc_perm msg_perm; /* Ownership and permissions */
//   time_t msg_stime;         /* Time of last msgsnd(2) */
//   time_t msg_rtime;         /* Time of last msgrcv(2) */
//   time_t msg_ctime;         /* Time of creation or last modification by msgctl() */
//   unsigned long msg_cbytes; /* # of bytes in queue */
//   msgqnum_t msg_qnum;       /* # number of messages in queue */
//   msglen_t msg_qbytes;      /* Maximum # of bytes in queue */
//   pid_t msg_lspid;          /* PID of last msgsnd(2) */
//   pid_t msg_lrpid;          /* PID of last msgrcv(2) */
// };

// 消息队列，消息队列控制
int main() {
  int msqid = msgget(0x1000, 0);
  printf("msqid=%d\r\n", msqid);
  printf("errno=%d,%s\r\n", errno, strerror(errno));

  struct msqid_ds buf;

  // msgctl() performs the control operation specified by cmd on the System V message queue with identifier msqid.
  // IPC_STAT
  // Copy information from the kernel data structure associated with msqid into the msqid_ds structure pointed to by buf.
  // The caller must have read permission on the message queue.
  int res = msgctl(msqid, IPC_STAT, &buf);

  // IPC_RMID
  // Immediately remove the message queue, awakening all waiting reader and writer processes (with an error return and errno set to EIDRM).
  // The calling process must have appropriate privileges or its effective user ID must be either that of the creator or owner of the message queue.
  // The third argument to msgctl() is ignored in this case.
  // int ret = msgctl(msqid, IPC_RMID, NULL);

  printf("msgctl res=%d,msg_qnum=%d\r\n", res, buf.msg_qnum);
  printf("errno=%d,%s\r\n", errno, strerror(errno));

  return 0;
}