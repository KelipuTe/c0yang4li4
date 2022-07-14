#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

/* ## 跳表 ## */

// 跳表为空时输出的无效值
#define UNDEFINED_SKIP_LIST_NODE (1 << 31)
// 跳表层数
// 最下面（层数最小）的那层会保存全部的结点
#define MAX_NUMBER_OF_PLIES 5

typedef struct SkipListNode {
  // 数值
  int num;
  // 这个结点的最大索引层数
  int numberOfPlies;
  // 指向这个结点在各索引层的下一个结点
  struct SkipListNode *arr1p1next[MAX_NUMBER_OF_PLIES];
} SkipListNode;

typedef struct SkipList {
  // 跳表头结点（第一个节点）
  struct SkipListNode *p1head;
  // 跳表长度
  int length;
} SkipList; // 跳表

// 初始化
extern SkipList *skipListInit();
// 输出跳表
extern void skipListPrint(SkipList *);
// 添加结点
extern void skipListAddNode(SkipList *, int);
// 移除结点
extern int skipListDeleteNode(SkipList *, int);

SkipList *skipListInit() {
  SkipList *p1 = (SkipList *)malloc(sizeof(SkipList));
  SkipListNode *p1node = (SkipListNode *)malloc(sizeof(SkipListNode));

  // 初始化跳表的时候需要额外初始化一个跳表头结点
  p1node->num = UNDEFINED_SKIP_LIST_NODE;
  p1node->numberOfPlies = UNDEFINED_SKIP_LIST_NODE;
  for (int i = 0; i < MAX_NUMBER_OF_PLIES; i++) {
    p1node->arr1p1next[i] = NULL;
  }

  p1->p1head = p1node;
  p1->length = 0;

  return p1;
}

void skipListPrint(SkipList *p1list) {
  SkipListNode *p1node;
  for (int i = MAX_NUMBER_OF_PLIES - 1; i >= 0; i--) {
    // 输出每层的时候都要重头开始
    p1node = p1list->p1head;
    printf("plies %d: ", i);
    while (p1node->arr1p1next[i] != NULL) {
      if (UNDEFINED_SKIP_LIST_NODE != p1node->numberOfPlies) {
        printf("%d,", p1node->num);
      }
      p1node = p1node->arr1p1next[i];
    }
    printf("%d,", p1node->num);
    printf("\r\n");
  }
}

void skipListAddNode(SkipList *p1list, int num) {
  // 本次插入的新结点
  SkipListNode *p1node = (SkipListNode *)malloc(sizeof(SkipListNode));
  // 每层索引中需要更新的那个结点
  SkipListNode *arr1p1update[MAX_NUMBER_OF_PLIES];
  SkipListNode *p1update = NULL;

  // 初始化每层索引中需要更新的那个结点为跳表头结点
  for (int i = 0; i < MAX_NUMBER_OF_PLIES; i++) {
    arr1p1update[i] = p1list->p1head;
  }

  p1update = p1list->p1head;
  // 找到插入新结点时，每层索引中需要更新的那个结点
  // 从高层开始遍历，因为高层是索引层，遍历速度快
  for (int i = MAX_NUMBER_OF_PLIES - 1; i >= 0; i--) {
    // 找到这层索引中，比目标值小的最大的结点
    while (p1update->arr1p1next[i] != NULL && p1update->arr1p1next[i]->num < num) {
      p1update = p1update->arr1p1next[i];
    }
    if (p1update->arr1p1next[i] != NULL && p1update->arr1p1next[i]->num == num) {
      // 发现表里已经存在要插入的结点，直接返回
      printf("find %d in list, jump over\r\n", num);
      return;
    }
    // 把需要更新的这个结点保存下来
    arr1p1update[i] = p1update;
    // 进入下面一层的遍历
  }

  p1node->num = num;
  // 通过类似抛硬币的算法，确定这个结点会出现哪几层中
  p1node->numberOfPlies = 0;
  for (int i = 0; i < MAX_NUMBER_OF_PLIES; i++) {
    if ((rand() % 2) == 0) {
      p1node->numberOfPlies++;
    }
  }
  for (int i = 0; i < MAX_NUMBER_OF_PLIES; i++) {
    p1node->arr1p1next[i] = NULL;
  }
  // 把新结点接到各层索引中去
  for (int i = p1node->numberOfPlies - 1; i >= 0; i--) {
    p1node->arr1p1next[i] = arr1p1update[i]->arr1p1next[i];
    arr1p1update[i]->arr1p1next[i] = p1node;
  }
}

int skipListDeleteNode(SkipList *p1list, int num) {
  SkipListNode *arr1p1update[MAX_NUMBER_OF_PLIES];
  SkipListNode *p1update = NULL;

  for (int i = 0; i < MAX_NUMBER_OF_PLIES; i++) {
    arr1p1update[i] = p1list->p1head;
  }

  p1update = p1list->p1head;
  for (int i = MAX_NUMBER_OF_PLIES - 1; i >= 0; i--) {
    while (p1update->arr1p1next[i] != NULL && p1update->arr1p1next[i]->num < num) {
      p1update = p1update->arr1p1next[i];
    }
    arr1p1update[i] = p1update;
  }
  // 上面那个循环结束之后，如果要删除的结点在跳表里
  // 那么 p1update 就会指向要删除的结点的前一个结点
  // 这里需要判断一下后面那个结点是不是要删除的结点
  if (p1update->arr1p1next[0] != NULL && p1update->arr1p1next[0]->num == num) {
    // 后面那个结点是要删除的结点
    // 获取一下结点出现哪几层中，每一个层都要删掉
    printf("delete %d in: ", num);
    for (int i = p1update->arr1p1next[0]->numberOfPlies - 1; i >= 0; i--) {
      printf("plies %d,", i);
      if (arr1p1update[i]->arr1p1next[i] != NULL && arr1p1update[i]->arr1p1next[i]->num == num) {
        arr1p1update[i]->arr1p1next[i] = arr1p1update[i]->arr1p1next[i]->arr1p1next[i];
      }
    }
    printf("\r\n");
  }
}
