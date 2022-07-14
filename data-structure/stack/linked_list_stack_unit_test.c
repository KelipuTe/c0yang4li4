#include "linked_list_stack.c"

// 单元测试
extern void LinkedListStackUnitTesting();

int main() {
  LinkedListStackUnitTesting();
  return 0;
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
