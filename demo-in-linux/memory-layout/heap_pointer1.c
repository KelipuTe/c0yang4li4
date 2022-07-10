#include <stdio.h>
#include <stdlib.h>

int main() {
  int *p1arr1;

  p1arr1 = malloc(sizeof(int) * 3);
  printf("&p1arr1   value=%p\r\n", &p1arr1);
  printf("p1arr1    value=%p\r\n", p1arr1);

  *p1arr1 = 1 << 4;
  *(p1arr1 + 1) = 1 << 8;
  *(p1arr1 + 2) = 1 << 12;
  printf("*p1arr1   value=%d\r\n", *p1arr1);
  printf("*p1arr1+1 value=%d\r\n", *(p1arr1 + 1));
  printf("*p1arr1+2 value=%d\r\n", *(p1arr1 + 2));

  free(p1arr1);
  p1arr1 = NULL;

  return 0;
}