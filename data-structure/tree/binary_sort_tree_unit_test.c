#include "binary_sort_tree.c"

void BinarySortTreeUnitTesting();

int main() {
  BinarySortTreeUnitTesting();
  return 0;
}

/**
 * 单元测试
 */
void BinarySortTreeUnitTesting() {
  // 指向根结点
  BinaryTreeNode *p1Root = NULL;

  int arr1Num[] = {55, 60, 11, 88, 27, 54, 74, 11, 69, 19};
  int arr1NumLen = (sizeof(arr1Num) / sizeof(int));

  for (int i = 0; i < arr1NumLen; i++) {
    AddNode(&p1Root, arr1Num[i]);
    DrawInConsole(p1Root);
  }

  InorderTraversal(p1Root);

  DeleteNode(p1Root, arr1Num[4]);

  InorderTraversal(p1Root);
}
