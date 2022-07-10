#include <stdio.h>
#include <stdlib.h>

int main() {
  int **p1;

  p1 = malloc(sizeof(int *) * 1);
  printf("&p1   value=%p\r\n", &p1);
  printf("p1    value=%p\r\n", p1);

  *p1 = malloc(sizeof(int) * 1);
  printf("&*p1  value=%p\r\n", &(*p1));
  printf("*p1   value=%p\r\n", *p1);

  **p1 = 1 << 4;
  printf("&**p1 value=%p\r\n", &(**p1));
  printf("**p1  value=%d\r\n", **p1);

  return 0;
}