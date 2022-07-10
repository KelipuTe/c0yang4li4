#include <stdio.h>

int main() {
  int a = 1 << 4;
  printf("&a start address=%p\r\n", &a);

  int b = 1 << 8;
  printf("&b start address=%p\r\n", &b);

  int c = 1 << 12;
  printf("&c start address=%p\r\n", &c);

  return 0;
}