#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <unistd.h>

struct msgbuf {
  long mtype;       /* message type, must be > 0 */
  char mtext[1024]; /* message data */
};

// 从消息队列读取消息
int main() {
  printf("[debug]:getpid()=%d\n", getpid());

  int mqId = msgget(0x1000, 0);
  printf("[debug]:mqId=%d, errno=%d, error=%s\n", mqId, errno, strerror(errno));

  struct msgbuf msg;

  // 从消息队列读取消息
  // ssize_t msgrcv(int msqid, void *msgp, size_t msgsz, long msgtyp, int msgflg);
  // msgflg = 0 时，没有消息时会阻塞
  // msgflg = IPC_NOWAIT 时，没有消息时会返回错误
  // msgflg = MSG_NOERROR 时，超长的消息会被截断
  int msgrcvResult = msgrcv(mqId, (void *)&msg, sizeof(msg.mtext), 0, IPC_NOWAIT);
  printf("[debug]:msgrcvResult=%d, msg.mtext=%s, msg.mtype=%ld\n", msgrcvResult, msg.mtext, msg.mtype);
  printf("[debug]:mqId=%d, errno=%d, error=%s\n", mqId, errno, strerror(errno));

  return 0;
}