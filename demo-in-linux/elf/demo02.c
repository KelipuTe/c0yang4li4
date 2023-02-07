#include <stdio.h>

int ga = 300;
int gb;

int func1() {
  static int si = 10;
  static int sj;

  printf("si=%d\n", si);
  si++;
}

int func2(int x) {
  int xx = x;
  printf("xx=%d\n", xx);
  return xx;
}

int main() {
  func1();
  func1();

  func2(1);
  func2(2);

  return 0;
}