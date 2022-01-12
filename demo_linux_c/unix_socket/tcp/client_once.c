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
  printf("socket(),sockfd=%d\r\n", sockfd);
  printf("errno=%d,%s\r\n", errno, strerror(errno));

  struct sockaddr_un addressAddr;
  addressAddr.sun_family = AF_UNIX;
  strcpy(addressAddr.sun_path, sockerFileName);

  int rtvl1 = connect(sockfd, (struct sockaddr *)&addressAddr, sizeof(addressAddr));
  printf("connect(),rtvl1=%d\r\n", rtvl1);
  printf("errno=%d,%s\r\n", errno, strerror(errno));

  char msg[1024] = {0};
  ssize_t rtvl2 = send(sockfd, "server", 6, 0);
  printf("send(),rtvl2=%d", rtvl2);
  printf("errno=%d,%s\r\n", errno, strerror(errno));

  ssize_t rtvl3 = recv(sockfd, msg, sizeof(msg), 0);
  printf("recv(),rtvl3=%d,msg=%s\r\n", rtvl3, msg);
  printf("errno=%d,%s\r\n", errno, strerror(errno));

  close(sockfd);

  return 0;
}