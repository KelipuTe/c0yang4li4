#include <stdio.h>
#include <stdlib.h>

/* ## 链表栈 ## */

// 栈为空时输出的无效值
#define UNDEFINED_STACK_NODE (1 << 31)

typedef struct LinkedListStackNode {
  // 数值
  int num;
  // 指向下一个结点的指针
  struct LinkedListStackNode *p1next;
} LinkedListStackNode; // 链表栈结点

typedef struct LinkedListStackHead {
  // 栈顶
  struct LinkedListStackNode *p1top;
  // 栈底
  struct LinkedListStackNode *p1bottom;
  // 栈长度
  int length;
} LinkedListStackHead; // 链表栈头结点

// 初始化链表栈
extern LinkedListStackHead *LinkedListStackInit();
// 输出栈
extern void LinkedListStackPrint(LinkedListStackHead *);
// 入栈
extern void LinkedListStackPush(LinkedListStackHead *, int);
// 出栈
extern int LinkedListStackPop(LinkedListStackHead *);
// 单元测试
extern void LinkedListStackUnitTesting();

int main() {
  LinkedListStackUnitTesting();
  return 0;
}

LinkedListStackHead *LinkedListStackInit() {
  LinkedListStackHead *p1 = (LinkedListStackHead *)malloc(sizeof(LinkedListStackHead));
  p1->p1top = NULL;
  p1->p1bottom = NULL;
  p1->length = 0;
  return p1;
}

void LinkedListStackPrint(LinkedListStackHead *p1head) {
  LinkedListStackNode *p1node = p1head->p1top;
  if (p1node == NULL) {
    printf("stack: empty\r\n");
    return;
  }
  printf("stack: ");
  while (p1node != NULL) {
    printf("%d,", p1node->num);
    p1node = p1node->p1next;
  }
  printf("\r\n");
}

void LinkedListStackPush(LinkedListStackHead *p1head, int num) {
  LinkedListStackNode *p1node = (LinkedListStackNode *)malloc(sizeof(LinkedListStackNode));
  p1node->num = num;
  if (p1head->p1top == NULL) {
    // 空栈
    p1node->p1next = NULL;
    p1head->p1top = p1node;
    p1head->p1bottom = p1node;
  } else {
    // 入栈
    p1node->p1next = p1head->p1top;
    // 移动栈顶
    p1head->p1top = p1node;
  }
}

int LinkedListStackPop(LinkedListStackHead *p1head) {
  LinkedListStackNode *p1node = p1head->p1top;
  int num = UNDEFINED_STACK_NODE;
  if (p1node == NULL) {
    printf("stack: empty\r\n");
    return num;
  }
  // 出栈
  num = p1node->num;
  printf("stack pop: %d\r\n", num);
  // 移动栈顶
  p1head->p1top = p1node->p1next;
  // 释放资源
  free(p1node);
  return num;
}

void LinkedListStackUnitTesting() {
  LinkedListStackHead *p1head = LinkedListStackInit();

  LinkedListStackPush(p1head, 1);

  LinkedListStackPop(p1head);
  LinkedListStackPop(p1head);

  LinkedListStackPush(p1head, 2);
  LinkedListStackPush(p1head, 3);

  LinkedListStackPrint(p1head);

  LinkedListStackPop(p1head);
  LinkedListStackPop(p1head);
  LinkedListStackPop(p1head);
}