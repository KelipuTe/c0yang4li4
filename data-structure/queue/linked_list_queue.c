#include <stdio.h>
#include <stdlib.h>

/* ## 链表队列 ## */

// 队列为空时输出的无效值
#define UNDEFINED_QUEUE_NODE (1 << 31)

typedef struct LinkedListQueueNode {
  // 数值
  int num;
  // 指向下一个结点的指针
  struct LinkedListQueueNode *p1next;
} LinkedListQueueNode; // 链表队列结点

typedef struct LinkedListQueueHead {
  // 队列头
  struct LinkedListQueueNode *p1head;
  //队列尾
  struct LinkedListQueueNode *p1tail;
  // 队列长度
  int length;
} LinkedListQueueHead; // 链表队列头结点

// 初始化
extern LinkedListQueueHead *LinkedListQueueInit();
// 输出队列
extern void LinkedListQueuePrint(LinkedListQueueHead *);
// 入队
extern void LinkedListQueuePush(LinkedListQueueHead *, int);
// 出队
extern int LinkedListQueuePop(LinkedListQueueHead *);
// 单元测试
extern void LinkedListQueueUnitTesting();

int main() {
  LinkedListQueueUnitTesting();
  return 0;
}

LinkedListQueueHead *LinkedListQueueInit() {
  LinkedListQueueHead *p1 = (LinkedListQueueHead *)malloc(sizeof(LinkedListQueueHead));
  p1->p1head = NULL;
  p1->p1tail = NULL;
  p1->length = 0;
  return p1;
}

void LinkedListQueuePrint(LinkedListQueueHead *p1head) {
  LinkedListQueueNode *p1node = p1head->p1head;
  if (p1node == NULL) {
    printf("queue: empty\r\n");
    return;
  }
  printf("queue: ");
  while (p1node != NULL) {
    printf("%d,", p1node->num);
    p1node = p1node->p1next;
  }
  printf("\r\n");
}

extern void LinkedListQueuePush(LinkedListQueueHead *p1head, int num) {
  LinkedListQueueNode *p1node = (LinkedListQueueNode *)malloc(sizeof(LinkedListQueueNode));
  p1node->num = num;
  p1node->p1next = NULL;
  if (p1head->p1head == NULL) {
    // 空队列
    p1head->p1head = p1node;
    p1head->p1tail = p1node;
  } else {
    // 入队队尾
    p1head->p1tail->p1next = p1node;
    // 移动队尾
    p1head->p1tail = p1node;
  }
}
int LinkedListQueuePop(LinkedListQueueHead *p1head) {
  LinkedListQueueNode *p1node = p1head->p1head;
  int num = UNDEFINED_QUEUE_NODE;
  if (p1node == NULL) {
    printf("queue: empty\r\n");
    return num;
  }
  // 出队队头
  num = p1node->num;
  printf("queue pop: %d\r\n", num);
  // 移动队头
  p1head->p1head = p1node->p1next;
  // 释放资源
  free(p1node);
  return num;
}

void LinkedListQueueUnitTesting() {
  LinkedListQueueHead *p1head = LinkedListQueueInit();

  LinkedListQueuePush(p1head, 1);

  LinkedListQueuePop(p1head);
  LinkedListQueuePop(p1head);

  LinkedListQueuePush(p1head, 2);
  LinkedListQueuePush(p1head, 3);

  LinkedListQueuePrint(p1head);

  LinkedListQueuePop(p1head);
  LinkedListQueuePop(p1head);
  LinkedListQueuePop(p1head);
}
