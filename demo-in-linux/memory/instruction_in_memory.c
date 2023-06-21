#include <stdio.h>

int methodA() {
  return 1024;
}

int main() {
  printf("&methodA=%p\n", &methodA);
  char *methodAByte = (char *)methodA;
  for (int i = 0; i < 15; i++) {
    printf("[%p]=%02x\n", methodAByte + i, *(methodAByte + i));
  };
  return 0;
}
