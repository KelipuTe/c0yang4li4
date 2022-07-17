#include <stdio.h>
#include <stdlib.h>

void GiveIntV1(int *);
void GiveIntV2(int **);

int main() {
  int *p1Int = NULL;

  printf("main, %p, %p\r\n", &p1Int, p1Int);
  // 把 main 里的 p1Int 指向的内存地址，拷贝了一份传给 GiveIntV1 里的 p1Int
  GiveIntV1(p1Int);
  printf("main, %p, %p\r\n", &p1Int, p1Int);

  printf("main, %p, %p\r\n", &p1Int, p1Int);
  // 把存储 main 里的 p1Int 的内存的内存地址，拷贝了一份传给 GiveIntV2 里的 p2Int
  GiveIntV2(&p1Int);
  printf("main, %p, %p\r\n", &p1Int, p1Int);

  return 0;
}

void GiveIntV1(int *p1Int) {
  printf("GiveIntV1, %p, %p\r\n", &p1Int, p1Int);
  // GiveIntV1 里的 p1Int 存储的是，main 的 p1Int 指向的内存地址
  // 申请了一块内存，让 GiveIntV1 里的 p1Int 指向这块内存地址
  // 这个操作没有修改 main 里的 p1Int 指向的内存地址，只是给 GiveIntV1 里的 p1Int 重新赋值
  p1Int = (int *)malloc(sizeof(int));
  printf("GiveIntV1, %p, %p\r\n", &p1Int, p1Int);
  *p1Int = 2;
}

void GiveIntV2(int **p2Int) {
  printf("GiveIntV2, %p, %p, %p\r\n", &p2Int, p2Int, *p2Int);
  // GiveIntV2 里的 p2Int 存储的是，存储 main 里的 p1Int 的内存的内存地址
  // 申请了一块内存，把这块内存的地址放到 main 里的 p1Int 的内存里去
  // 这个操作修改了 main 里的 p1Int 指向的内存地址，
  *p2Int = (int *)malloc(sizeof(int));
  printf("GiveIntV2, %p, %p, %p\r\n", &p2Int, p2Int, *p2Int);
  **p2Int = 2;
}