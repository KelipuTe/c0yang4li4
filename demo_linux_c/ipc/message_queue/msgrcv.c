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

// 从消息队列接收消息
int main() {
  int mqid = msgget(0x1000, 0);
  printf("msgget(),mqid=%d\r\n", mqid);
  printf("errno=%d,%s\r\n", errno, strerror(errno));

  struct msgbuf msg;

  // msgrcv(2)
  // #include <sys/msg.h>
  // msgflg=0时，没有消息时会阻塞
  // msgflg=IPC_NOWAIT时，没有消息时会返回错误
  // msgflg=MSG_NOERROR，超长的消息会被截断
  int rtvl2 = msgrcv(mqid, (void *)&msg, sizeof(msg.mtext), 0, IPC_NOWAIT);
  printf("msgrcv(),rtvl2=%d,msg.mtext=%s,msg.mtype=%d\r\n", rtvl2, msg.mtext, msg.mtype);
  printf("errno=%d,%s\r\n", errno, strerror(errno));

  return 0;
}