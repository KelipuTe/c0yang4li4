#include "array_stack.c"

// 单元测试
extern void ArrayStackUnitTesting();

int main() {
  ArrayStackUnitTesting();
  return 0;
}

void ArrayStackUnitTesting() {
  ArrayStack *p1stack = ArrayStackInit();

  ArrayStackPush(p1stack, 1);

  ArrayStackPop(p1stack);
  ArrayStackPop(p1stack);

  ArrayStackPush(p1stack, 2);
  ArrayStackPush(p1stack, 3);

  ArrayStackPrint(p1stack);

  ArrayStackPop(p1stack);
  ArrayStackPop(p1stack);
  ArrayStackPop(p1stack);
}
