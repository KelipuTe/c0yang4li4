#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>
#include <sys/wait.h>
#include <unistd.h>

// 匿名 unix socket
int main() {
  printf("[debug]:unix socket unnamed, getpid()=%d\n", getpid());

  int fds[2];

  // 创建一对匿名 unix socket
  int socketpairResult = socketpair(AF_UNIX, SOCK_STREAM | SOCK_NONBLOCK, 0, fds);
  printf("[debug]:socketpairResult=%d\n", socketpairResult);
  printf("[debug]:errno=%d, error=%s\n", errno, strerror(errno));

  pid_t pid = fork();
  if (pid == 0) {
    printf("[debug]:unix socket unnamed, child, getpid()=%d\n", getpid());
    // 关掉不用的那个
    close(fds[1]);

    while (1) {
      char msg[128] = {0};
      int recvByteNum = recv(fds[0], msg, sizeof(msg), 0);
      printf("[debug]:child, recvByteNum=%d, msg=%s\n", recvByteNum, msg);
      printf("[debug]:errno=%d, error=%s\n", errno, strerror(errno));
      if (recvByteNum <= 0) {
        printf("[debug]:child, recvByteNum<=0\n");
        break;
      }
      sleep(1);
    }

    close(fds[0]);

    return 0;
  }
  printf("[debug]:unix socket unnamed, parent, getpid()=%d\n", getpid());
  // 关掉不用的那个
  close(fds[0]);

  int sendByteNum = write(fds[1], "parent", 6);
  printf("[debug]:sendByteNum=%d\n", sendByteNum);
  printf("[debug]:errno=%d, error=%s\n", errno, strerror(errno));

  close(fds[1]);

  wait(0);

  return 0;
}