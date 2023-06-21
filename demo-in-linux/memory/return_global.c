#include <stdio.h>

int globalI = 1024;

int methodA(){
  return globalI;
}

int main() {
  printf("&globalI=%p\n", &globalI);
  printf("&methodA=%p\n", &methodA);
  return 0;
}
