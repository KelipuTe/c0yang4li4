#include "linked_list_queue.c"

// 单元测试
extern void LinkedListQueueUnitTesting();

int main() {
  LinkedListQueueUnitTesting();
  return 0;
}

void LinkedListQueueUnitTesting() {
  LinkedListQueue *p1queue = LinkedListQueueInit();

  LinkedListQueuePush(p1queue, 1);

  LinkedListQueuePop(p1queue);
  LinkedListQueuePop(p1queue);

  LinkedListQueuePush(p1queue, 2);
  LinkedListQueuePush(p1queue, 3);

  LinkedListQueuePrint(p1queue);

  LinkedListQueuePop(p1queue);
  LinkedListQueuePop(p1queue);
  LinkedListQueuePop(p1queue);
}
