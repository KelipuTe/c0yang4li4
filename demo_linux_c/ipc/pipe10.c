#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

// 匿名管道
int main() {
  // pipe() creates a pipe, a unidirectional data channel that can be used for interprocess communication.
  // The array pipefd is used to return two file descriptors referring to the ends of the pipe.
  // pipefd[0] refers to the read end of the pipe. pipefd[1] refers to the write end of the pipe.
  int pipefd[2] = {0};
  int result = pipe(pipefd);

  pid_t pid = fork();
  if (pid == 0) {
    char data;
    // 这里要关闭写管道，要不然接收不到父进程写管道关闭的信号
    close(pipefd[1]);
    // 子进程读取父进程的数据
    while (read(pipefd[0], &data, 1) > 0) {
      printf("%c", data);
    }
    printf("\r\n");
    close(pipefd[0]);

    return 0;
  }
  // 要关闭读管道
  close(pipefd[0]);
  // 父进程给子进程发送数据
  write(pipefd[1], "hello", 5);
  // 当这里关闭时，子进程还在读pipefd[0]的话，就会返回0，表示父进程的pipefd[1]已经关闭了
  close(pipefd[1]);

  wait(0);

  return 0;
}