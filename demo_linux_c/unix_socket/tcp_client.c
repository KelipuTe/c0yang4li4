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
  char sockerFileName[] = "/tmp/unix_tcp";

  int sockfd = socket(AF_LOCAL, SOCK_STREAM, 0);

  struct sockaddr_un addressAddr, clientAddr;
  addressAddr.sun_family = AF_UNIX;
  strcpy(addressAddr.sun_path, sockerFileName);

  int returnValue = connect(sockfd, (struct sockaddr *)&addressAddr, sizeof(addressAddr));
  printf("connect returnValue=%d\r\n", returnValue);
  printf("errno=%d,%s\r\n", errno, strerror(errno));

  char msg[1024] = {0};
  ssize_t sendValue = send(sockfd, "server", 6, 0);
  printf("client send bytes=%d", sendValue);

  ssize_t recvValue = recv(sockfd, msg, sizeof(msg), 0);
  printf("client recv bytes=%d,msg=%s\r\n", recvValue, msg);

  close(sockfd);

  return 0;
}