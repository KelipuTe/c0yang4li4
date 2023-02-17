#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  printf("call by exec, pid=%d\n", getpid());
  printf("call by exec, argc=%d, argv[0]=%s, argv[1]=%s\n", argc, argv[0], argv[1]);
  return 1;
}