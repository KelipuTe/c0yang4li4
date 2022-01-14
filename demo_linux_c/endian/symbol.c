#include <stdio.h>

int a = 300;

int main() {
  // 输出变量的地址
  printf("&a=%p\r\n", &a);
  // 用符号表中的地址直接访问变量
  printf("a=%d\r\n", *(int *)(0x601034));
  // 输出main函数的地址
  printf("&main=%p\r\n", main);
  // 甚至可以通过地址直接调用main函数
  typedef int (*func)();
  ((int (*)())(0x40052d))();

  return 0;
}