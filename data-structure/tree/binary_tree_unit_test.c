#include "binary_tree.c"

// 单元测试
extern int BinaryTreeUnitTesting();

int main() {
  BinaryTreeUnitTesting();
  return 0;
}

int BinaryTreeUnitTesting() {
  // 用数组保存的二叉树结构
  int arr1Num[] = {1, 2, 3, 4, 5, 6, 7, UNDEFINED_NODE_VALUE, UNDEFINED_NODE_VALUE, 10, 11};
  int arr1NumLen = sizeof(arr1Num) / sizeof(int);
  // 根结点指针
  BinaryTreeNode *p1Root = NULL;
  BuildBinaryTreeFromArray(&p1Root, arr1Num, arr1NumLen, 1);

  printf("PreorderTraversal: ");
  PreorderTraversal(p1Root);
  printf("\r\n");

  printf("InorderTraversal: ");
  InorderTraversal(p1Root);
  printf("\r\n");

  printf("SubsequentTraversal: ");
  SubsequentTraversal(p1Root);
  printf("\r\n");

  printf("GetDepth: %d\r\n", GetDepth(p1Root));

  printf("BreadthFirstSearch: ");
  BreadthFirstSearch(p1Root);
  printf("\r\n");

  printf("DepthFirstSearch: ");
  DepthFirstSearch(p1Root);
  printf("\r\n");

  return 0;
}
