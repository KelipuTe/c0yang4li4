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

typedef struct LinkedListStack {
  // 栈顶
  struct LinkedListStackNode *p1top;
  // 栈长度
  int length;
} LinkedListStack; // 链表栈

// 初始化链表栈
extern LinkedListStack *LinkedListStackInit();
// 输出栈
extern void LinkedListStackPrint(LinkedListStack *);
// 入栈
extern void LinkedListStackPush(LinkedListStack *, int);
// 出栈
extern int LinkedListStackPop(LinkedListStack *);
// 单元测试
extern void LinkedListStackUnitTesting();

// int main() {
//   LinkedListStackUnitTesting();
//   return 0;
// }

LinkedListStack *LinkedListStackInit() {
  LinkedListStack *p1 = (LinkedListStack *)malloc(sizeof(LinkedListStack));
  p1->p1top = NULL;
  p1->length = 0;
  return p1;
}

void LinkedListStackPrint(LinkedListStack *p1stack) {
  LinkedListStackNode *p1node = p1stack->p1top;
  if (NULL == p1node) {
    printf("stack: empty\r\n");
    return;
  }
  printf("length=%d, stack: ", p1stack->length);
  while (p1node != NULL) {
    printf("%d,", p1node->num);
    p1node = p1node->p1next;
  }
  printf("\r\n");
}

void LinkedListStackPush(LinkedListStack *p1stack, int num) {
  LinkedListStackNode *p1node = (LinkedListStackNode *)malloc(sizeof(LinkedListStackNode));
  p1node->num = num;
  if (NULL == p1stack->p1top) {
    // 空栈
    p1node->p1next = NULL;
    p1stack->p1top = p1node;
  } else {
    // 入栈
    p1node->p1next = p1stack->p1top;
    // 移动栈顶
    p1stack->p1top = p1node;
  }
  p1stack->length++;
}

int LinkedListStackPop(LinkedListStack *p1stack) {
  LinkedListStackNode *p1node = p1stack->p1top;
  int num = UNDEFINED_STACK_NODE;
  if (NULL == p1node) {
    printf("stack: empty\r\n");
    return num;
  }
  // 出栈
  num = p1node->num;
  printf("stack pop: %d\r\n", num);
  // 移动栈顶
  p1stack->p1top = p1node->p1next;
  p1stack->length--;
  // 释放资源
  free(p1node);
  return num;
}

void LinkedListStackUnitTesting() {
  LinkedListStack *p1stack = LinkedListStackInit();

  LinkedListStackPush(p1stack, 1);

  LinkedListStackPop(p1stack);
  LinkedListStackPop(p1stack);

  LinkedListStackPush(p1stack, 2);
  LinkedListStackPush(p1stack, 3);

  LinkedListStackPrint(p1stack);

  LinkedListStackPop(p1stack);
  LinkedListStackPop(p1stack);
  LinkedListStackPop(p1stack);
}