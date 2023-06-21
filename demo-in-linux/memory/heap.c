#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
  printf("pid=%d\n", getpid());

  int *p7LocalJ;
  p7LocalJ = malloc(sizeof(int));
  *p7LocalJ = 2048;
  printf("*p7LocalJ=%x,p7LocalJ=%p\n", *p7LocalJ, p7LocalJ);
  free(p7LocalJ);

  return 0;
}