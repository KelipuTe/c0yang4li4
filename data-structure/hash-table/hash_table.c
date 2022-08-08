#include <stdio.h>
#include <stdlib.h>

// ## 哈希表 ##

#include "../linked-list/singly_linked_list.c"

// 哈希表最大长度
#define HASH_TABLE_MAX_LENGTH 10

typedef struct HashTable {
  // 内部链表头结点数组
  SinglyLinkedList *arr1p1Table[HASH_TABLE_MAX_LENGTH];
  // 哈希表结点总数
  int totalNum;
} HashTable; // 哈希表

// 哈希函数
extern int hashFunc(int num);
// 初始化哈希表
extern HashTable *hashTableInit();
// 输出哈希表
extern void hashTablePrint(HashTable *);
// 添加结点
extern void hashTableAddNode(HashTable *, int);
// 移除结点
extern void hashTableDeleteNode(HashTable *, int);

int hashFunc(int num) {
  return num % HASH_TABLE_MAX_LENGTH;
}

HashTable *hashTableInit() {
  HashTable *p1 = (HashTable *)malloc(sizeof(HashTable));
  for (int i = 0; i < HASH_TABLE_MAX_LENGTH; i++) {
    p1->arr1p1Table[i] = singlyLinkedListInit();
  }
  p1->totalNum = 0;
  return p1;
}

void hashTablePrint(HashTable *p1table) {
  printf("hashTablePrint: totalNum=%d, \r\n", p1table->totalNum);
  for (int i = 0; i < HASH_TABLE_MAX_LENGTH; i++) {
    printf("mod=%d, ", i);
    singlyLinkedListPrint(p1table->arr1p1Table[i]);
  }
}

void hashTableAddNode(HashTable *p1table, int num) {
  p1table->totalNum++;
  singlyLinkedListAddNode(p1table->arr1p1Table[hashFunc(num)], num);
}

void hashTableDeleteNode(HashTable *p1table, int num) {
  p1table->totalNum -= singlyLinkedListDeleteNode(p1table->arr1p1Table[hashFunc(num)], num);
}
