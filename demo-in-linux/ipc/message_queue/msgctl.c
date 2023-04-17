#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <unistd.h>

// 消息队列控制
int main() {
  printf("[debug]:getpid()=%d\n", getpid());

  int mqId = msgget(0x1000, 0);
  printf("[debug]:mqId=%d, errno=%d, error=%s\n", mqId, errno, strerror(errno));

  // msgqnum_t       msg_qnum;   /* # number of messages in queue */
  struct msqid_ds buf;
  // int msgctl(int msqid, int cmd, struct msqid_ds *buf);
  // 当 cmd = IPC_STAT 时，读取消息队列状态
  // 当 cmd = IPC_RMID 时，删除消息队列
  int msgctlResult = msgctl(mqId, IPC_STAT, &buf);
  printf("[debug]:msgctlResult=%d, buf.msg_qnum=%ld\n", msgctlResult, buf.msg_qnum);
  printf("[debug]:mqId=%d, errno=%d, error=%s\n", mqId, errno, strerror(errno));

  return 0;
}