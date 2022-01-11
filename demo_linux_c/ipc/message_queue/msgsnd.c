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

// 向消息队列发送消息
int main() {
  int mqid = msgget(0x1000, 0);
  printf("msgget(),mqid=%d\r\n", mqid);
  printf("errno=%d,%s\r\n", errno, strerror(errno));

  struct msgbuf msg;
  msg.mtype = 1;
  strcpy(msg.mtext, "hello");

  // msgsnd(2)
  // #include <sys/msg.h>
  // msgsnd()用于向消息队列发送消息
  // 当msgflg=MSG_NOERROR时，超长的消息会被截断
  int rtvl2 = msgsnd(mqid, (void *)&msg, sizeof(msg.mtext), 0);
  printf("msgsnd(),rtvl2=%d\r\n", rtvl2);
  printf("errno=%d,%s\r\n", errno, strerror(errno));

  return 0;
}