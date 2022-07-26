#include "balanced_binary_tree.c"

void BalancedSortTreeUnitTesting();

int main() {
  BalancedSortTreeUnitTesting();
  return 0;
}

/**
 * 单元测试
 */
void BalancedSortTreeUnitTesting() {
  // 指向根结点
  BalancedBinaryTreeNode *p1Root = NULL;

  // int arr1Num[] = {55, 60, 11, 88, 27, 54, 74, 11, 69, 19};
  int arr1Num[] = {1, 23, 45, 34, 98, 9, 4, 35, 23, 74, 11};
  int arr1NumLen = (sizeof(arr1Num) / sizeof(int));

  for (int i = 0; i < arr1NumLen; i++) {
    AddNode(&p1Root, arr1Num[i]);
  }

  InorderTraversal(p1Root);
}
