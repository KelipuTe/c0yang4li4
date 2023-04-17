#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

// 匿名管道
int main() {
  printf("[debug]:parent, getpid()=%d\n", getpid());

  // 创建一对文件描述符，0 用于读，1 用于写
  int pipefd[2] = {0};
  int pipeResult = pipe(pipefd);
  printf("[debug]:parent, pipeResult=%d, errno=%d, error=%s\n", pipeResult, errno, strerror(errno));

  pid_t pid = fork();
  if (pid == 0) {
    // 子进程要关闭写管道，要不然接收不到父进程关闭写管道的信号
    close(pipefd[1]);
    // 子进程读取父进程的数据
    int readByteNum = 1;
    char data;
    while (readByteNum > 0) {
      // 从文件描述符中读取数据，每次读取一个字节
      // 能读到数据就继续读，读不到数据就结束
      readByteNum = read(pipefd[0], &data, 1);
      if (readByteNum > 0) {
        printf("[debug]:child,readByteNum=%d, data=%c\n", readByteNum, data);
      } else {
        printf("\n");
        break;
      }
    }
    close(pipefd[0]);

    return 0;
  }
  // 父进程要关闭读管道
  close(pipefd[0]);
  // 父进程给子进程发送数据，向文件描述符中写入数据，写 5 个字节
  int writeByteNum = write(pipefd[1], "hello", 5);
  printf("[debug]:parent, writeByteNum=%d\n", writeByteNum);
  // 当这里关闭时，子进程还在读的话，就会返回 0，表示父进程已经关闭了
  close(pipefd[1]);
  // 父进程回收子进程
  wait(0);

  return 0;
}