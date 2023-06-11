#include <stdio.h>

// 动态库
// gcc -fPIC -shared library.c -o library.so

void print_hello_world() {
  printf("hello, world\n");
}