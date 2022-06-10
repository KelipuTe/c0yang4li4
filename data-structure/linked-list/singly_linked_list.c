#include <stdio.h>
#include <stdlib.h>

/* ## 单链表 ## */

typedef struct SinglyLinkedListHead {
  // 头指针
  struct SinglyLinkedListNode *p1head;
  // 尾指针
  struct SinglyLinkedListNode *p1tail;
  // 链表长度
  int length;
} SinglyLinkedListHead; // 头结点

typedef struct SinglyLinkedListNode {
  // 数值
  int num;
  // 指向下一个结点的指针
  struct SinglyLinkedListNode *p1next;
} SinglyLinkedListNode; // 链表结点

// 初始化单链表
extern SinglyLinkedListHead *singlyLinkedListInit();
// 输出链表
extern void singlyLinkedListPrint(SinglyLinkedListHead *);
// 添加结点
extern void singlyLinkedListAddNode(SinglyLinkedListHead *, int);
// 移除结点
extern void singlyLinkedListDeleteNode(SinglyLinkedListHead *, int);
// 单元测试
extern void singlyLinkedListUnitTesting();

// int main() {
//  singlyLinkedListUnitTesting();
//  return 0;
// }

SinglyLinkedListHead *singlyLinkedListInit() {
  SinglyLinkedListHead *p1 = (SinglyLinkedListHead *)malloc(sizeof(SinglyLinkedListHead));
  p1->p1head = NULL;
  p1->p1tail = NULL;
  p1->length = 0;
  return p1;
}

void singlyLinkedListPrint(SinglyLinkedListHead *p1head) {
  SinglyLinkedListNode *p1node;
  printf("singlyLinkedListPrint: length=%d, list=", p1head->length);
  if (p1head->length > 0) {
    // 注意空表
    p1node = p1head->p1head;
    while (p1node != NULL) {
      printf("%d,", p1node->num);
      p1node = p1node->p1next;
    }
  }
  printf("\r\n");
}

void singlyLinkedListAddNode(SinglyLinkedListHead *p1head, int num) {
  SinglyLinkedListNode *p1node = (SinglyLinkedListNode *)malloc(sizeof(SinglyLinkedListNode));

  p1node->num = num;
  p1node->p1next = NULL;
  if (p1head->length == 0) {
    // 链表为空
    p1head->p1head = p1node;
    p1head->p1tail = p1node;
  } else {
    // 链表不为空，则把结点连接到链表尾部
    p1head->p1tail->p1next = p1node;
    p1head->p1tail = p1node;
  }
  p1head->length++;
}

void singlyLinkedListDeleteNode(SinglyLinkedListHead *p1head, int num) {
  // 当前结点，上一个结点
  SinglyLinkedListNode *p1now = p1head->p1head;
  SinglyLinkedListNode *p1prev = NULL;

  if (p1now != NULL) {
    while (p1now != NULL) {
      if (p1now->num == num) {
        // 找到要删除的节点
        if (p1now == p1head->p1head) {
          // 刚好是头
          p1head->p1head = p1head->p1head->p1next;
          free(p1now);
          p1now = p1head->p1head;
        } else if (p1now == p1head->p1tail) {
          // 刚好是尾
          p1prev->p1next = NULL;
          p1head->p1tail = p1prev;
          free(p1now);
          p1now = NULL;
        } else {
          // 连接当前结点的前一个结点和后一个结点
          p1prev->p1next = p1now->p1next;
          free(p1now);
          p1now = p1prev->p1next;
        }
        p1head->length--;
      } else {
        // 指针后移继续寻找
        p1prev = p1now;
        p1now = p1now->p1next;
      }
    }
  }
}

void singlyLinkedListUnitTesting() {
  SinglyLinkedListHead *p1listHead = singlyLinkedListInit();

  singlyLinkedListPrint(p1listHead);

  singlyLinkedListDeleteNode(p1listHead, 2);
  singlyLinkedListPrint(p1listHead);

  singlyLinkedListAddNode(p1listHead, 2);
  singlyLinkedListAddNode(p1listHead, 4);
  singlyLinkedListAddNode(p1listHead, 6);
  singlyLinkedListAddNode(p1listHead, 4);
  singlyLinkedListAddNode(p1listHead, 6);
  singlyLinkedListPrint(p1listHead);

  singlyLinkedListDeleteNode(p1listHead, 4);
  singlyLinkedListPrint(p1listHead);

  singlyLinkedListAddNode(p1listHead, 8);
  singlyLinkedListPrint(p1listHead);

  singlyLinkedListDeleteNode(p1listHead, 2);
  singlyLinkedListPrint(p1listHead);
}
