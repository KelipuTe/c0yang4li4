#include <stdio.h>

int main() {
  int x = 10;
  int y = 100;
  for (int i = 0; i < 10; i++) {
    x++;
    printf("i=%d,x=%d\n", i, x);
    y++;
    printf("i=%d,y=%d\n", i, y);
  }
  return 0;
}