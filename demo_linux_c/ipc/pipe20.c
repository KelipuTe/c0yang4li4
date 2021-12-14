#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

// 命名管道，父子进程
int main() {
  // Pipes and FIFOs (also known as named pipes) provide a unidirectional interprocess communication channel.
  // A pipe has a read end and a write end.  Data written to the write end of a pipe can be read from the read end of the pipe.

  // A FIFO (short for First In First Out) has a name within the filesystem (created using mkfifo(3)), and is opened using open(2).
  // Any process may open a FIFO, assuming the file permissions allow it.
  // The read end is opened using the O_RDONLY flag; the write end is opened using the O_WRONLY flag.
  // See fifo(7) for further details.
  // Note: although FIFOs have a pathname in the filesystem, I/O on FIFOs does not involve operations on the underlying device (if there is one).

  // 判断文件fifo是否存在，不存在就创建
  if (access("./fifo", F_OK)) {
    int result = mkfifo("./fifo", 0666);
    printf("errno=%d,%s\r\n", errno, strerror(errno));
  }

  pid_t pid = fork();
  if (pid == 0) {
    char data;
    // 打开读取文件标识符
    int fdRead = open("./fifo", O_RDONLY);
    while (read(fdRead, &data, 1) > 0) {
      printf("%c", data);
    }
    printf("\r\n");
    close(fdRead);

    return 0;
  }
  // 写入读取文件标识符
  int fdWrite = open("./fifo", O_WRONLY);
  write(fdWrite, "hello", 5);
  // 当这里关闭时，子进程还在读pipefd[0]的话，就会返回0，表示父进程的pipefd[1]已经关闭了
  close(fdWrite);

  wait(0);

  return 0;
}