#include "circular_linked_list.c"

/* ## 约瑟夫问题 ## */

int main() {
  int totalNum = 41;

  CircularLinkedList *p1circularLinkedList = circularLinkedListInit();

  for (int i = 1; i <= totalNum; i++) {
    circularLinkedListAddNode(p1circularLinkedList, i);
  }

  circularLinkedListPrint(p1circularLinkedList);

  // 当前结点，上一个结点
  CircularLinkedListNode *p1now = p1circularLinkedList->p1head;
  CircularLinkedListNode *p1prev = NULL;

  // 约瑟夫问题
  printf("kill: ");
  for (int i = 0; i < totalNum; i++) {
    // 跳过两个人，杀第三个人
    for (int j = 0; j < 2; j++) {
      p1prev = p1now;
      p1now = p1now->p1next;
    }
    printf("%d,", p1now->num);
    if (p1circularLinkedList->p1head == p1circularLinkedList->p1tail) {
      // 就剩一个结点了
      p1circularLinkedList->p1head = NULL;
      p1circularLinkedList->p1tail = NULL;
      free(p1now);
      break;
    }
    if (p1now == p1circularLinkedList->p1head) {
      p1circularLinkedList->p1head = p1circularLinkedList->p1head->p1next;
      p1circularLinkedList->p1tail->p1next = p1circularLinkedList->p1head;
      free(p1now);
      p1now = p1circularLinkedList->p1head;
    } else if (p1now == p1circularLinkedList->p1tail) {
      p1prev->p1next = NULL;
      p1circularLinkedList->p1tail = p1prev;
      p1circularLinkedList->p1tail->p1next = p1circularLinkedList->p1head;
      free(p1now);
      p1now = p1prev->p1next;
    } else {
      p1prev->p1next = p1now->p1next;
      free(p1now);
      p1now = p1prev->p1next;
    }

    p1circularLinkedList->length--;
  }
  printf("\r\n");

  circularLinkedListPrint(p1circularLinkedList);
}