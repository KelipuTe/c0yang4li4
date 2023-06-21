#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
  printf("pid=%d\n", getpid());

  int localI = 1024;
  int *p7LocalI = &localI;
  int **p7LocalII = &p7LocalI;

  printf("localI=%d,&localI=%p\n", localI, &localI);
  printf("*p7LocalI=%d,p7LocalI=%p,&p7LocalI=%p\n", *p7LocalI, p7LocalI, &p7LocalI);
  printf("*p7LocalII=%p,p7LocalII=%p,&p7LocalII=%p\n", *p7LocalII, p7LocalII, &p7LocalII);

  return 0;
}