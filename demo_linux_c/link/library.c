#include <stdio.h>

// 动态库
// gcc -fPIC -shared library.c -o library.so

void print_hello() {
  printf("hello, world\r\n");
}