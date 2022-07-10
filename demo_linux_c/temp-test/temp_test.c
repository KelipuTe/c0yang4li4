#include <stdio.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>
int num = 300;
int main() {
  printf("tcp server start,getpid()=%d\r\n", getpid());
  printf("num:%p\r\n",&num);
  printf("main:%p\r\n",main);
  char *data = "test";
  printf("data:%p\r\n",data);
  int bf = 9502;
  printf("bf:%p\r\n",&bf);
  getchar();
  return 0;
}