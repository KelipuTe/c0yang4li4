#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

// 匿名管道
int main() {
  int pipefd[2] = {0};
  // pipe(2)
  // #include <unistd.h>
  // 创建一对文件描述符，0用于读，1用于写
  int rtvl1 = pipe(pipefd);
  printf("pipe(),rtvl1=%d\r\n", rtvl1);
  printf("errno=%d,%s\r\n", errno, strerror(errno));

  pid_t pid = fork();
  if (pid == 0) {
    // 子进程要关闭写管道，要不然接收不到父进程关闭写管道的信号
    close(pipefd[1]);
    // 子进程读取父进程的数据
    int rtvl2 = 1;
    char data;
    while (rtvl2 > 0) {
      // read(2)
      // #include <unistd.h>
      // 从文件描述符中读取数据，每次读取一个字节
      // 能读到数据就继续读，读不到数据就结束
      rtvl2 = read(pipefd[0], &data, 1);
      if (rtvl2 > 0) {
        printf("rtvl2=%d,data=%c\r\n", rtvl2, data);
      } else {
        printf("\r\n");
        break;
      }
    }
    close(pipefd[0]);

    return 0;
  }
  // 父进程要关闭读管道
  close(pipefd[0]);
  // 父进程给子进程发送数据
  // write(2)
  // #include <unistd.h>
  // 向文件描述符中写入数据，写5个字节
  write(pipefd[1], "hello", 5);
  // 当这里关闭时，子进程还在读的话，就会返回0，表示父进程已经关闭了
  close(pipefd[1]);

  wait(0);

  return 0;
}