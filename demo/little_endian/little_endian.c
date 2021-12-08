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

  printf("%d=>0b100101100(2)\r\n", 0b100101100); //2进制
  printf("%d=>0454(8)\r\n", 0454);               //8进制
  printf("%d=>300(10)\r\n", 300);                //10进制
  printf("%d=>0x012c(16)\r\n", 0x012c);          //16进制
  //300的16进制是0x2c01，但是在内存中的存储方式是小端字节序
  //所以直接输出0x2c01，在内存中表示的是11265
  printf("%d=>11265\r\n", 0x2c01);

  return 0;
}