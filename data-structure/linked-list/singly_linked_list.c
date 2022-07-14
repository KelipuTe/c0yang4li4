#include <stdio.h>
#include <stdlib.h>

/* ## 单链表 ## */

typedef struct SinglyLinkedListNode {
  // 数值
  int num;
  // 指向下一个结点的指针
  struct SinglyLinkedListNode *p1next;
} SinglyLinkedListNode; // 链表结点

typedef struct SinglyLinkedList {
  // 头指针
  struct SinglyLinkedListNode *p1head;
  // 尾指针
  struct SinglyLinkedListNode *p1tail;
  // 链表长度
  int length;
} SinglyLinkedList; // 单链表

// 初始化单链表
extern SinglyLinkedList *singlyLinkedListInit();
// 输出链表
extern void singlyLinkedListPrint(SinglyLinkedList *);
// 添加结点
extern void singlyLinkedListAddNode(SinglyLinkedList *, int);
// 移除结点
extern int singlyLinkedListDeleteNode(SinglyLinkedList *, int);

SinglyLinkedList *singlyLinkedListInit() {
  SinglyLinkedList *p1 = (SinglyLinkedList *)malloc(sizeof(SinglyLinkedList));
  p1->p1head = NULL;
  p1->p1tail = NULL;
  p1->length = 0;
  return p1;
}

void singlyLinkedListPrint(SinglyLinkedList *p1list) {
  SinglyLinkedListNode *p1node = p1list->p1head;
  if (NULL == p1node) {
    // 空链表
    printf("list: empty\r\n");
    return;
  }
  printf("singlyLinkedListPrint: length=%d, list=", p1list->length);
  while (p1node != NULL) {
    printf("%d,", p1node->num);
    p1node = p1node->p1next;
  }
  printf("\r\n");
}

void singlyLinkedListAddNode(SinglyLinkedList *p1list, int num) {
  SinglyLinkedListNode *p1node = (SinglyLinkedListNode *)malloc(sizeof(SinglyLinkedListNode));
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
  p1list->length++;
}

int singlyLinkedListDeleteNode(SinglyLinkedList *p1list, int num) {
  // 当前结点，上一个结点
  SinglyLinkedListNode *p1now = p1list->p1head;
  SinglyLinkedListNode *p1prev = NULL;
  // 删除结点的个数
  int deleteNum = 0;
  if (NULL == p1now) {
    return deleteNum;
  }
  while (p1now != NULL) {
    if (p1now->num == num) {
      // 找到要删除的节点
      if (p1now == p1list->p1head) {
        // 刚好是头
        p1list->p1head = p1list->p1head->p1next;
        // 释放资源
        free(p1now);
        p1now = p1list->p1head;
      } else if (p1now == p1list->p1tail) {
        // 刚好是尾
        p1prev->p1next = NULL;
        p1list->p1tail = p1prev;
        // 释放资源
        free(p1now);
        p1now = NULL;
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
  }
  return deleteNum;
}
