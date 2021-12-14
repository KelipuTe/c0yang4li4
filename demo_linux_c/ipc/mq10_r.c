#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>

struct msgbuf {
  long mtype;       /* message type, must be > 0 */
  char mtext[1024]; /* message data */
};

int main() {
  int msqid = msgget(0x1000, 0);
  printf("msqid=%d\r\n", msqid);
  printf("error=%d,error=%s\r\n", errno, strerror(errno));

  struct msgbuf msg;

  // The msgrcv() system call removes a message from the queue specified by msqid and places it in the buffer pointed to by msgp.
  // msgflg=0，没有消息时会阻塞
  // int res = msgrcv(msqid, (void *)&msg, sizeof(msg.mtext), 0, 0);

  // IPC_NOWAIT
  // Return immediately if no message of the requested type is in the queue.  The system call fails with errno set to ENOMSG.
  // msgflg=IPC_NOWAIT，没有消息时会返回错误
  int res = msgrcv(msqid, (void *)&msg, sizeof(msg.mtext), 0, IPC_NOWAIT);

  // MSG_NOERROR
  // To truncate the message text if longer than msgsz bytes.
  // 消息队列的消息的长度超过msgsz参数时，消息会被截断
  // int res = msgrcv(msqid, (void *)&msg, 5, 1, MSG_NOERROR);

  printf("msgrcv res=%d,mtext=%s,mtype=%d\r\n", res, msg.mtext, msg.mtype);
  printf("error=%d,error=%s\r\n", errno, strerror(errno));

  return 0;
}