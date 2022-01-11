#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>

// 创建消息队列
int main() {
  // 创建一个新的消息队列，返回消息队列id
  // msgget(2)
  // #include <sys/msg.h>
  // 引用一个现存的或者创建一个新的消息队列标识符
  // 第一个参数key用于唯一标识一个消息队列
  int mqid = msgget(0x1000, IPC_CREAT | IPC_EXCL | 0666);
  printf("msgget(),mqid=%d\r\n", mqid);
  printf("errno=%d,%s\r\n", errno, strerror(errno));

  return 0;
}