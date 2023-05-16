#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
  printf("[debug]:unix tcp client start, getpid()=%d\n", getpid());

  char sockerFileName[] = "/tmp/unix_tcp";

  int sockfd = socket(AF_LOCAL, SOCK_STREAM, 0);
  printf("[debug]:sockfd=%d\n", sockfd);
  printf("[debug]:errno=%d, error=%s\n", errno, strerror(errno));

  struct sockaddr_un addressAddr;
  addressAddr.sun_family = AF_UNIX;
  strcpy(addressAddr.sun_path, sockerFileName);

  int connectResult = connect(sockfd, (struct sockaddr *)&addressAddr, sizeof(addressAddr));
  printf("[debug]:connectResult=%d\n", connectResult);
  printf("[debug]:errno=%d, error=%s\n", errno, strerror(errno));

  char msg[1024] = {0};
  ssize_t sendByteNum = send(sockfd, "server", 6, 0);
  printf("[debug]:sendByteNum=%ld\n", sendByteNum);
  printf("[debug]:errno=%d, error=%s\n", errno, strerror(errno));

  ssize_t recvByteNum = recv(sockfd, msg, sizeof(msg), 0);
  printf("[debug]:recvByteNum=%ld, msg=%s\n", recvByteNum, msg);
  printf("[debug]:errno=%d, error=%s\n", errno, strerror(errno));


  close(sockfd);

  return 0;
}