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
  printf("[debug]:parent, getpid()=%d\n", getpid());

  // 判断 fifo 文件是否存在，不存在就创建
  // access() 用于检查用户是否有某个文件的权限，也可以变相用于检查文件存不存在
  if (access("/tmp/fifo", F_OK)) {
    int mkfifoResult = mkfifo("/tmp/fifo", 0666);
    printf("[debug]:parent, mkfifoResult=%d, errno=%d, error=%s\n", mkfifoResult, errno, strerror(errno));
  }

  pid_t pid = fork();
  if (pid == 0) {
    // 子进程打开 fifo 文件，读取父进程的数据
    int fdRead = open("/tmp/fifo", O_RDONLY);
    printf("[debug]:child, fdRead=%d\n", fdRead);

    int readByteNum = 1;
    char data;
    while (readByteNum > 0) {
      readByteNum = read(fdRead, &data, 1);
      if (readByteNum > 0) {
        printf("[debug]:child, readByteNum=%d, data=%c\n", readByteNum, data);
      } else {
        printf("\n");
        break;
      }
    }
    close(fdRead);

    return 0;
  }
  // 父进程打开 fifo 文件，写入给子进程发送的数据
  int fdWrite = open("/tmp/fifo", O_WRONLY);
  int writeByteNum = write(fdWrite, "hello", 5);
  printf("[debug]:parent, writeByteNum=%d\n", writeByteNum);
  // 当这里关闭时，子进程还在读的话，就会返回 0，表示父进程已经关闭了
  close(fdWrite);
  // 父进程回收子进程
  wait(0);

  return 0;
}