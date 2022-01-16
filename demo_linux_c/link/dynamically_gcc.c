#include <stdio.h>
#include <stdlib.h>

// 编译的时候链接动态库
// gcc dynamically_gcc.c ./library.so -o dynamically_gcc

void print_hello();

int main() {
  print_hello();
  return 0;
}