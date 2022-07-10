#include <stdio.h>

int main() {
  int arr1[4] = {1 << 4,1 << 8,1 << 12,1 << 16};
  printf("&arr1 start address=%p\r\n", &arr1);

  int arr2[2][2] = {{1 << 4,1 << 8},{1 << 12,1 << 16}};
  printf("&arr2 start address=%p\r\n", &arr2);

  return 0;
}