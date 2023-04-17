#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <unistd.h>

// 创建消息队列
int main() {
  printf("[debug]:getpid()=%d\n", getpid());

  // 创建一个新的或者引用一个现存的消息队列，返回消息队列 id
  // int msgget(key_t key, int msgflg);
  // 第一个参数 key 用于唯一标识一个消息队列
  int mqId = msgget(0x1000, IPC_CREAT | IPC_EXCL | 0666);
  printf("[debug]:mqId=%d, errno=%d, error=%s\n", mqId, errno, strerror(errno));

  return 0;
}