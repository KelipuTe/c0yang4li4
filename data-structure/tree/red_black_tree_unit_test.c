#include "red_black_tree.c"

void RedBlackTreeUnitTesting();

int main() {
  RedBlackTreeUnitTesting();
  return 0;
}

void RedBlackTreeUnitTesting() {
  // 指向根结点
  RedBlackTreeNode *p1Root = NULL;
  // nil 结点
  RedBlackTreeNode nilNode = {INT_MIN, NULL, NULL, NULL, BLACK};

  int arr1Num[] = {87, 29, 87, 65, 25, 33, 78, 12, 5, 85};
  int arr1NumLen = (sizeof(arr1Num) / sizeof(int));

  for (int i = 0; i < arr1NumLen; i++) {
    AddNode(&p1Root, arr1Num[i], &nilNode);
  }

  InorderTraversal(p1Root, &nilNode);

  DeleteNode(&p1Root, arr1Num[4], &nilNode);

  InorderTraversal(p1Root, &nilNode);
}