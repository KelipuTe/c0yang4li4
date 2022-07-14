#include "hash_table.c"

// 单元测试
extern void hashTableUnitTesting();

int main() {
  hashTableUnitTesting();
  return 0;
}

void hashTableUnitTesting() {
  HashTable *p1hashTable = hashTableInit();

  hashTableDeleteNode(p1hashTable, 2);

  hashTableAddNode(p1hashTable, 2);
  hashTableAddNode(p1hashTable, 4);
  hashTableAddNode(p1hashTable, 6);
  hashTableAddNode(p1hashTable, 4);
  hashTableAddNode(p1hashTable, 6);

  hashTablePrint(p1hashTable);

  hashTableDeleteNode(p1hashTable, 4);

  hashTableAddNode(p1hashTable, 8);

  hashTableDeleteNode(p1hashTable, 2);

  hashTablePrint(p1hashTable);
}
