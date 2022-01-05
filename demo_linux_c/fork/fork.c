#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
  printf("[debug]:parent,getpid()=%d\r\n", getpid());
  // fork(2)
  // #include <unistd.h>
  // creates a new process by duplicating the calling process，通过复制调用进程来创建子进程
  // 子进程从fork()这行开始执行，子进程会拿到0，父进程会拿到子进程pid
  pid_t pid = fork();

  if (pid == -1) {
    printf("[error]:fock(),failed\r\n");
    // errno
    // #include <errno.h>
    // system error numbers，系统错误码
    // strerror(3)
    // #include <string.h>
    // return string describing error number，返回系统错误码对应的文案
    printf("[error]:errno=%d,errstr%s\r\n", errno, strerror(errno));
  }

  if (pid == 0) {
    printf("[debug]:child,pid=%d\r\n", pid);
    printf("[debug]:child,getpid()=%d\r\n", getpid());
  } else {
    sleep(2);
    printf("[debug]:parent,pid=%d\r\n", pid);
  }

  return 0;
}