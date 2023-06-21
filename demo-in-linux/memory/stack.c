#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
  printf("pid=%d\n", getpid());

  int localI = 1024;
  printf("localI=%x,&localI=%p\n", localI, &localI);

  return 0;
}