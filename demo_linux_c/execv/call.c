#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  printf("call,new,pid=%d\r\n", getpid());
  printf("call,argc=%d\r\n", argc);
  printf("call,argv[0]=%s\r\n", argv[0]);
  printf("call,argv[1]=%s\r\n", argv[1]);

  return 1;
}