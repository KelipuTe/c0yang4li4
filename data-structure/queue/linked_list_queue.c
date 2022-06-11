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

typedef struct LinkedListQueue {
  // 队列头
  struct LinkedListQueueNode *p1head;
  // 队列尾
  struct LinkedListQueueNode *p1tail;
  // 队列长度
  int length;
} LinkedListQueue; // 链表队列头结点

// 初始化
extern LinkedListQueue *LinkedListQueueInit();
// 输出队列
extern void LinkedListQueuePrint(LinkedListQueue *);
// 入队
extern void LinkedListQueuePush(LinkedListQueue *, int);
// 出队
extern int LinkedListQueuePop(LinkedListQueue *);
// 单元测试
extern void LinkedListQueueUnitTesting();

int main() {
  LinkedListQueueUnitTesting();
  return 0;
}

LinkedListQueue *LinkedListQueueInit() {
  LinkedListQueue *p1 = (LinkedListQueue *)malloc(sizeof(LinkedListQueue));
  p1->p1head = NULL;
  p1->p1tail = NULL;
  p1->length = 0;
  return p1;
}

void LinkedListQueuePrint(LinkedListQueue *p1queue) {
  LinkedListQueueNode *p1node = p1queue->p1head;
  if (NULL == p1node) {
    printf("queue: empty\r\n");
    return;
  }
  printf("length=%d, queue: ", p1queue->length);
  while (p1node != NULL) {
    printf("%d,", p1node->num);
    p1node = p1node->p1next;
  }
  printf("\r\n");
}

extern void LinkedListQueuePush(LinkedListQueue *p1queue, int num) {
  LinkedListQueueNode *p1node = (LinkedListQueueNode *)malloc(sizeof(LinkedListQueueNode));
  p1node->num = num;
  p1node->p1next = NULL;
  if (NULL == p1queue->p1head) {
    // 空队列
    p1queue->p1head = p1node;
    p1queue->p1tail = p1node;
  } else {
    // 入队队尾
    p1queue->p1tail->p1next = p1node;
    // 移动队尾
    p1queue->p1tail = p1node;
  }
  p1queue->length++;
}
int LinkedListQueuePop(LinkedListQueue *p1queue) {
  LinkedListQueueNode *p1node = p1queue->p1head;
  int num = UNDEFINED_QUEUE_NODE;
  if (NULL == p1node) {
    printf("queue: empty\r\n");
    return num;
  }
  // 出队队头
  num = p1node->num;
  printf("queue pop: %d\r\n", num);
  // 移动队头
  p1queue->p1head = p1node->p1next;
  p1queue->length--;
  // 释放资源
  free(p1node);
  return num;
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
