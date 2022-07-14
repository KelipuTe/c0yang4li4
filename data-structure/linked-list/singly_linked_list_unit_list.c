#include "singly_linked_list.c"

// 单元测试
extern void singlyLinkedListUnitTesting();

int main() {
  singlyLinkedListUnitTesting();
  return 0;
}

void singlyLinkedListUnitTesting() {
  SinglyLinkedList *p1list = singlyLinkedListInit();

  singlyLinkedListPrint(p1list);

  singlyLinkedListDeleteNode(p1list, 2);
  singlyLinkedListPrint(p1list);

  singlyLinkedListAddNode(p1list, 2);
  singlyLinkedListAddNode(p1list, 4);
  singlyLinkedListAddNode(p1list, 6);
  singlyLinkedListAddNode(p1list, 4);
  singlyLinkedListAddNode(p1list, 6);
  singlyLinkedListPrint(p1list);

  singlyLinkedListDeleteNode(p1list, 4);
  singlyLinkedListPrint(p1list);

  singlyLinkedListAddNode(p1list, 8);
  singlyLinkedListPrint(p1list);

  singlyLinkedListDeleteNode(p1list, 2);
  singlyLinkedListPrint(p1list);
}
