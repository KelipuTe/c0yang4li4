#include <stdio.h>

int ga = 300;

int main() {
  // 输出全局变量 ga 的地址
  printf("&ga=%p\n", &ga);
  // 输出 main 函数的地址
  printf("&main=%p\n", main);

  // 通过符号表中的地址直接访问变量
  // printf("ga=%d\n", *(int *)(0x4010));
  // 通过符号表中的地址直接调用 main 函数
  // typedef int (*func)();
  // ((int (*)())(0x1149))();

  return 0;
}