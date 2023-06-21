#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
  printf("pid=%d\n", getpid());

  char strA[16] = "stringA";
  printf("&strA=%p,strA=%s\n", strA, strA);

  char *strB = "stringB";
  printf("&strB=%p,strB=%s\n", strB, strB);
  strB = "stringBB";
  printf("&strB=%p,strB=%s\n", strB, strB);

  char *strC;
  strC = malloc(sizeof(char) * 8);
  strcpy(strC, "stringC");
  printf("&strC=%p,strC=%s\n", strC, strC);
  printf("malloc_usable_size(strC)=%ld\n", malloc_usable_size(strC));

  free(strC);

  return 0;
}