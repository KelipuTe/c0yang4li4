#include "binary_tree.c"

// 单元测试
extern int BinaryTreeUnitTesting();

int main() {
  BinaryTreeUnitTesting();
  return 0;
}

int BinaryTreeUnitTesting() {
  // 根结点指针
  BinaryTreeNode *p1Root = NULL;

  int arr1Num[] = {UNDEFINED_NODE_VALUE, 1, 2, 3, 4, 5, 6, 7, UNDEFINED_NODE_VALUE, UNDEFINED_NODE_VALUE, 10, 11};
  int arr1NumLen = (sizeof(arr1Num) / sizeof(int));

  BuildBinaryTreeFromArray(&p1Root, arr1Num, arr1NumLen, 1);

  PreorderTraversal(p1Root);
  InorderTraversal(p1Root);
  SubsequentTraversal(p1Root);

  printf("GetDepth: %d\r\n", GetDepth(p1Root));

  BreadthFirstSearch(p1Root);
  DepthFirstSearch(p1Root);

  return 0;
}
