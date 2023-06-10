#include <stdio.h>

int globalIntA;
int globalIntB = 300;

int functionA(int localIntI) {
  int localIntJ = localIntI;
  printf("functionA, localIntI=%d, localIntI=%d\n", localIntI, localIntJ);
  return localIntJ;
}

int functionB() {
  static int staticIntA;
  static int staticIntB = 10;

  printf("functionX, staticIntB=%d\n", staticIntB);
  staticIntB++;
}

int functionC() {
  printf("functionC, globalIntB=%d\n", globalIntB);
  globalIntB++;
}

int main() {
  functionA(1);
  functionA(2);

  functionB();
  functionB();

  functionC();
  functionC();

  return 0;
}