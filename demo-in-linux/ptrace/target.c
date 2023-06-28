#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
  int data = 200;

  while (1) {
    printf("getpid()=%d,data=%x,&data=%p\n", getpid(), data, &data);
    sleep(2);
  }

  return 0;
}