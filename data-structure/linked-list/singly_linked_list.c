#include <stdio.h>
#include <stdlib.h>

/* ## 单链表 ## */

typedef struct ListHead {
  // 头指针
  struct ListNode *p1head;
  // 尾指针
  struct ListNode *p1tail;
  // 结点数量
  int totalNum;
} ListHead; // 头结点

typedef struct ListNode {
  // 数值
  int num;
  // 指向下一个结点的指针
  struct ListNode *p1next;
} ListNode; // 链表结点

// 初始化头结点
extern ListHead *initList();
// 输出链表
extern void printList(ListHead *);
// 添加结点
extern void addNode(ListHead *, int);
// 移除结点
extern void deleteNode(ListHead *, int);

int main() {
  ListHead *p1listHead = initList();

  printList(p1listHead);

  deleteNode(p1listHead, 2);
  printList(p1listHead);

  addNode(p1listHead, 2);
  addNode(p1listHead, 4);
  addNode(p1listHead, 6);
  addNode(p1listHead, 4);
  addNode(p1listHead, 6);
  printList(p1listHead);

  deleteNode(p1listHead, 4);
  printList(p1listHead);

  addNode(p1listHead, 8);
  printList(p1listHead);

  deleteNode(p1listHead, 2);
  printList(p1listHead);

  return 0;
}

ListHead *initList() {
  ListHead *p1 = (ListHead *)malloc(sizeof(ListHead));
  p1->p1head = NULL;
  p1->p1tail = NULL;
  p1->totalNum = 0;
  return p1;
}

void printList(ListHead *p1head) {
  ListNode *p1node;
  printf("list:");
  if (p1head->totalNum > 0) {
    // 注意空表
    p1node = p1head->p1head;
    while (p1node != NULL) {
      printf("%d,", p1node->num);
      p1node = p1node->p1next;
    }
  }
  printf("\r\n");
}

void addNode(ListHead *p1head, int num) {
  ListNode *p1node = (ListNode *)malloc(sizeof(ListNode));

  p1node->num = num;
  p1node->p1next = NULL;
  if (p1head->totalNum == 0) {
    // 链表为空
    p1head->p1head = p1node;
    p1head->p1tail = p1node;
  } else {
    // 链表不为空，则把结点连接到链表尾部
    p1head->p1tail->p1next = p1node;
    p1head->p1tail = p1node;
  }
  p1head->totalNum++;
}

void deleteNode(ListHead *p1head, int num) {
  // 当前结点，上一个结点
  ListNode *p1now = p1head->p1head;
  ListNode *p1prev = NULL;

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
        p1head->totalNum--;
      } else {
        // 指针后移继续寻找
        p1prev = p1now;
        p1now = p1now->p1next;
      }
    }
  }
}