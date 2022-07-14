#include "circular_linked_list.c"

// 单元测试
extern void circularLinkedListUnitTesting();

int main() {
  circularLinkedListUnitTesting();
  return 0;
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
