#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>

// 消息队列控制
int main() {
  int mqid = msgget(0x1000, 0);
  printf("msgget(),mqid=%d\r\n", mqid);
  printf("errno=%d,%s\r\n", errno, strerror(errno));

  struct msqid_ds buf;

  // msgctl(2)
  // #include <sys/msg.h>
  // 当cmd=IPC_STAT时，读取消息队列状态
  // 当cmd=IPC_RMID时，删除消息队列
  int rtvl1 = msgctl(mqid, IPC_STAT, &buf);
  printf("msgctl(),rtvl1=%d,buf.msg_qnum=%d\r\n", rtvl1, buf.msg_qnum);
  printf("errno=%d,%s\r\n", errno, strerror(errno));

  return 0;
}