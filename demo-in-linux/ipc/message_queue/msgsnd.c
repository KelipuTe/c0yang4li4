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

// 向消息队列发送消息
int main() {
  printf("[debug]:getpid()=%d\n", getpid());

  int mqId = msgget(0x1000, 0);
  printf("[debug]:mqId=%d, errno=%d, error=%s\n", mqId, errno, strerror(errno));

  struct msgbuf msg;
  msg.mtype = 1;
  strcpy(msg.mtext, "hello");

  // 用于向消息队列发送消息
  // int msgsnd(int msqid, const void *msgp, size_t msgsz, int msgflg);
  // 当 msgflg = MSG_NOERROR 时，超长的消息会被截断
  int msgsndResult = msgsnd(mqId, (void *)&msg, sizeof(msg.mtext), 0);
  printf("[debug]:msgsndResult=%d\n", msgsndResult);
  printf("[debug]:mqId=%d, errno=%d, error=%s\n", mqId, errno, strerror(errno));

  return 0;
}