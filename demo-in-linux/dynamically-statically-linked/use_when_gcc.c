#include <stdio.h>
#include <stdlib.h>

// 编译的时候链接动态库
// gcc dynamically_gcc.c ./library.so -o dynamically_gcc

void print_hello_world();

int main() {
  print_hello_world();
  return 0;
}