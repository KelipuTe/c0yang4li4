#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>

// 消息队列，消息队列创建
int main() {
  // A new message queue is created if key has the value IPC_PRIVATE
  // or key isn't IPC_PRIVATE, no message queue with the given key key exists, and IPC_CREAT is specified in msgflg.
  // If msgflg specifies both IPC_CREAT and IPC_EXCL and a message queue already exists for key,
  // then msgget() fails with errno set to EEXIST.  (This is analogous to the effect of the combination O_CREAT | O_EXCL for open(2).)

  // 创建一个新的消息队列，返回消息队列id
  int msqid = msgget(0x1000, IPC_CREAT | IPC_EXCL | 0666);

  // 引用一个现存的消息队列，返回消息队列id
  // int msqid = msgget(0x1000, 0);

  printf("msqid=%d\r\n", msqid);
  printf("errno=%d,%s\r\n", errno, strerror(errno));

  return 0;
}