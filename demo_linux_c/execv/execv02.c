#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  printf("new,pid=%d\r\n", getpid());

  printf("argc=%d\r\n", argc);

  printf("argv[0]=%s\r\n", argv[0]);
  printf("argv[1]=%s\r\n", argv[1]);

  return 1;
}