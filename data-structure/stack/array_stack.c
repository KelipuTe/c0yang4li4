#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ## 数组栈 ## */

// 栈为空时输出的无效值
#define UNDEFINED_STACK_NODE (1 << 31)
// 数组栈最大长度
#define ARRAY_STACK_MAX_LENGTH 256

typedef struct ArrayStack {
  // 数组栈
  int arr1stack[ARRAY_STACK_MAX_LENGTH];
  // 栈顶
  int top;
  // 栈长度
  int length;
} ArrayStack; // 数组栈

// 初始化数组栈
extern ArrayStack *ArrayStackInit();
// 输出栈
extern void ArrayStackPrint(ArrayStack *);
// 入栈
extern void ArrayStackPush(ArrayStack *, int);
// 出栈
extern int ArrayStackPop(ArrayStack *);

ArrayStack *ArrayStackInit() {
  ArrayStack *p1 = (ArrayStack *)malloc(sizeof(ArrayStack));
  memset(p1->arr1stack, 0, sizeof(p1->arr1stack));
  // 因为数组下标从 0 开始，所以空栈时，栈顶应该在 -1 的位置
  p1->top = -1;
  p1->length = 0;
  return p1;
}

void ArrayStackPrint(ArrayStack *p1stack) {
  int index = p1stack->top;
  if (-1 == index) {
    printf("stack: empty\r\n");
    return;
  }
  printf("length=%d, stack: ", p1stack->length);
  while (index != -1) {
    printf("%d,", p1stack->arr1stack[index]);
    index--;
  }
  printf("\r\n");
}

void ArrayStackPush(ArrayStack *p1stack, int num) {
  p1stack->top++;
  p1stack->arr1stack[p1stack->top] = num;
  p1stack->length++;
}

int ArrayStackPop(ArrayStack *p1stack) {
  int num = UNDEFINED_STACK_NODE;
  if (-1 == p1stack->top) {
    printf("stack: empty\r\n");
    return num;
  }
  num = p1stack->arr1stack[p1stack->top];
  printf("stack pop: %d\r\n", num);
  p1stack->top--;
  p1stack->length--;
  return num;
}
