#include <stdio.h>
#include <stdlib.h>

/* ## 循环链表 ## */

typedef struct CircularLinkedListNode {
  // 数值
  int num;
  // 指向下一个结点的指针
  struct CircularLinkedListNode *p1next;
} CircularLinkedListNode; // 链表结点

typedef struct CircularLinkedList {
  // 头指针
  struct CircularLinkedListNode *p1head;
  // 尾指针
  struct CircularLinkedListNode *p1tail;
  // 链表长度
  int length;
} CircularLinkedList; // 循环链表

// 初始化单链表
extern CircularLinkedList *circularLinkedListInit();
// 输出链表
extern void circularLinkedListPrint(CircularLinkedList *);
// 添加结点
extern void circularLinkedListAddNode(CircularLinkedList *, int);
// 移除结点
extern int circularLinkedListDeleteNode(CircularLinkedList *, int);
// 单元测试
extern void circularLinkedListUnitTesting();

int main() {
  circularLinkedListUnitTesting();
  return 0;
}

CircularLinkedList *circularLinkedListInit() {
  CircularLinkedList *p1 = (CircularLinkedList *)malloc(sizeof(CircularLinkedList));
  p1->p1head = NULL;
  p1->p1tail = NULL;
  p1->length = 0;
  return p1;
}

void circularLinkedListPrint(CircularLinkedList *p1list) {
  CircularLinkedListNode *p1node = p1list->p1head;
  if (NULL == p1node) {
    // 空链表
    printf("list: empty\r\n");
    return;
  }
  printf("circularLinkedListPrint: length=%d, list=", p1list->length);
  do {
    printf("%d,", p1node->num);
    p1node = p1node->p1next;
    // 当又一次回到第一个结点时，遍历结束
  } while (p1node != NULL && p1node != p1list->p1head);
  printf("\r\n");
}
void circularLinkedListAddNode(CircularLinkedList *p1list, int num) {
  CircularLinkedListNode *p1node = (CircularLinkedListNode *)malloc(sizeof(CircularLinkedListNode));
  p1node->num = num;
  p1node->p1next = NULL;
  if (NULL == p1list->p1head) {
    // 链表为空
    p1list->p1head = p1node;
    p1list->p1tail = p1node;
  } else {
    // 链表不为空，则把结点连接到链表尾部
    p1list->p1tail->p1next = p1node;
    p1list->p1tail = p1node;
  }
  // 尾首相接
  p1list->p1tail->p1next = p1list->p1head;
  p1list->length++;
}
int circularLinkedListDeleteNode(CircularLinkedList *p1list, int num) {
  // 当前结点，上一个结点
  CircularLinkedListNode *p1now = p1list->p1head;
  CircularLinkedListNode *p1prev = NULL;
  // 删除结点的个数
  int deleteNum = 0;
  if (NULL == p1now) {
    return deleteNum;
  }
  do {
    if (p1now->num == num) {
      // 找到要删除的节点
      if (p1list->p1head == p1list->p1tail) {
        // 就剩一个结点了
        p1list->p1head = NULL;
        p1list->p1tail = NULL;
        free(p1now);
        break;
      }
      if (p1now == p1list->p1head) {
        // 刚好是头
        p1list->p1head = p1list->p1head->p1next;
        // 重新连接尾首
        p1list->p1tail->p1next = p1list->p1head;
        // 释放资源
        free(p1now);
        p1now = p1list->p1head;
      } else if (p1now == p1list->p1tail) {
        // 刚好是尾
        p1prev->p1next = NULL;
        p1list->p1tail = p1prev;
        // 重新连接尾首
        p1list->p1tail->p1next = p1list->p1head;
        // 释放资源
        free(p1now);
        p1now = p1prev->p1next;
      } else {
        // 连接当前结点的前一个结点和后一个结点
        p1prev->p1next = p1now->p1next;
        // 释放资源
        free(p1now);
        p1now = p1prev->p1next;
      }
      p1list->length--;
      deleteNum++;
    } else {
      // 指针后移继续寻找
      p1prev = p1now;
      p1now = p1now->p1next;
    }
  } while (p1now != NULL && p1now != p1list->p1head);
  return deleteNum;
}

void circularLinkedListUnitTesting() {
  CircularLinkedList *p1list = circularLinkedListInit();

  circularLinkedListPrint(p1list);

  circularLinkedListDeleteNode(p1list, 2);
  circularLinkedListPrint(p1list);

  circularLinkedListAddNode(p1list, 2);
  circularLinkedListAddNode(p1list, 4);
  circularLinkedListAddNode(p1list, 6);
  circularLinkedListAddNode(p1list, 4);
  circularLinkedListAddNode(p1list, 6);
  circularLinkedListPrint(p1list);

  circularLinkedListDeleteNode(p1list, 4);
  circularLinkedListPrint(p1list);

  circularLinkedListAddNode(p1list, 8);
  circularLinkedListPrint(p1list);

  circularLinkedListDeleteNode(p1list, 2);
  circularLinkedListPrint(p1list);
}
