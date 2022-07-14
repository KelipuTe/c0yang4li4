#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#include "skip_list.c"

// 单元测试
extern void skipListUnitTesting();

int main() {
  skipListUnitTesting();
  return 0;
}

void skipListUnitTesting() {
  srand(time(NULL));

  // 构造随机序列
  int arr1num[50] = {61, 51, 81, 90, 89, 90, 19, 45, 80, 28, 71, 92, 9, 58, 68, 78, 9, 19, 89, 20, 4, 73, 25, 76, 87, 72, 60, 17, 2, 83, 82, 55, 35, 2, 37, 19, 93, 21, 8, 24, 50, 69, 75, 50, 39, 9, 37, 42, 5, 96};
  int arr1numLength = 50;
  // for (int i = 0; i < arr1numLength; i++) {
  //   arr1num[i] = (rand() % 99) + 1;
  // }
  // printf("arr1num: ");
  // for (int i = 0; i < arr1numLength; i++) {
  //   printf("%d,", arr1num[i]);
  // }
  // printf("\r\n");

  SkipList *p1list = skipListInit();

  for (int i = 0; i < arr1numLength; i++) {
    skipListAddNode(p1list, arr1num[i]);
  }

  skipListPrint(p1list);

  skipListDeleteNode(p1list, arr1num[28]);
  skipListDeleteNode(p1list, arr1num[20]);
  skipListDeleteNode(p1list, arr1num[10]);

  skipListPrint(p1list);
}
