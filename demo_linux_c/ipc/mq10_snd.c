#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>

// The msgp argument is a pointer to a caller-defined structure of the following general form:
struct msgbuf {
  long mtype;       /* message type, must be > 0 */
  char mtext[1024]; /* message data */
};
// The mtext field is an array (or other structure) whose size is specified by msgsz, a nonnegative integer value.
// Messages of zero length (i.e., no mtext field) are permitted.
// The mtype field must have a strictly positive integer value.
// This value can be used by the receiving process for message selection (see the description of msgrcv() below).

// 消息队列，发送消息
int main() {
  int msqid = msgget(0x1000, 0);
  printf("msqid=%d\r\n", msqid);
  printf("error=%d,error=%s\r\n", errno, strerror(errno));

  struct msgbuf msg;
  msg.mtype = 1;
  strcpy(msg.mtext, "hello");

  // The msgsnd() system call appends a copy of the message pointed to by msgp to the message queue whose identifier is specified by msqid.
  int res = msgsnd(msqid, (void *)&msg, sizeof(msg.mtext), 0);

  // MSG_NOERROR
  // To truncate the message text if longer than msgsz bytes.
  // 消息队列的消息的长度超过msgsz参数时，消息会被截断
  // int res = msgsnd(msqid, (void *)&msg, 3, MSG_NOERROR);

  printf("msgsnd res=%d\r\n", res);
  printf("errno=%d,%s\r\n", errno, strerror(errno));

  return 0;
}