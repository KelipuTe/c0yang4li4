#include <stdio.h>

int a = 300;
int b;

int func1(int x) {
  int y = x;
  printf("%d\r\n", y);
  return y;
}

int main() {
  static int i = 10;
  static int j;
  func1(i);
  return 0;
}