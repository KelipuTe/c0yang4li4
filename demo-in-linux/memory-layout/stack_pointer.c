#include <stdio.h>

int main() {
  int a = 1 << 4;
  printf("  &a start address=%p\r\n", &a);
  printf("   a         value=%d\r\n", a);

  int *p1a = &a;
  printf("&p1a start address=%p\r\n", &p1a);
  printf(" p1a         value=%p\r\n", p1a);

  int **p2a = &p1a;
  printf("&p2a start address=%p\r\n", &p2a);
  printf(" p2a         value=%p\r\n", p2a);

  return 0;
}