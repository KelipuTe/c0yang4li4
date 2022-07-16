#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 输出 int 类型的一维数组
extern void PrintArr1(int *, int);
// 构造一维数组，随机填充 int 类型的数据
extern void MakeArr1Int();

void PrintArr1Int(int *p1arr1, int arr1Len) {
  printf("arr1: ");
  for (int i = 0; i < arr1Len; i++) {
    printf("%d,", p1arr1[i]);
  }
  printf("\r\n");
}

void MakeArr1Int() {
  int arr1[10];
  int arr1Len = 10;

  srand(time(NULL));
  for (int i = 0; i < arr1Len; i++) {
    arr1[i] = rand() % 99 + 1;
  }

  PrintArr1Int(arr1, arr1Len);
}