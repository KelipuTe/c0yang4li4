#include <stdio.h>

int main() {
  // 100101100（2进制）、0454（8进制）、300（10进制）、012C（16进制）
  printf("%d=>0b100101100(2)\r\n", 0b100101100);
  printf("%d=>0454(8)\r\n", 0454);
  printf("%d=>300(10)\r\n", 300);
  printf("%d=>0x012c(16)\r\n", 0x012c);
  printf("%d=>11265\r\n", 0x2c01);
  return 0;
}