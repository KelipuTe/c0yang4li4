#include "binary_tree.c"

// 单元测试
void BinaryTreeUnitTesting();

int main() {
  BinaryTreeUnitTesting();
  return 0;
}

void BinaryTreeUnitTesting() {
  HANDLE consolehend;
  consolehend= GetStdHandle(STD_OUTPUT_HANDLE);
  SetConsoleTextAttribute(consolehend,0xc);
  printf("INT_MIN = %d\r\n", INT_MIN);
  printf("INT_MAX = +%d\r\n", INT_MAX);
  printf("TIER_NUM_MAX      = %d\r\n", TIER_NUM_MAX);
  printf("TIER_NODE_NUM_MAX = %d\r\n", TIER_NODE_NUM_MAX);
  printf("TREE_NODE_NUM_MAX = %d\r\n", TREE_NODE_NUM_MAX);

  // 指向根结点
  BinaryTreeNode *p1Root = NULL;

  int arr1Num[] = {INT_MIN, 1, 2, 3, 4, 5, 6, 7, INT_MIN, INT_MIN, 10, 11};
  int arr1NumLen = (sizeof(arr1Num) / sizeof(int));

  BuildBinaryTreeFromArray(&p1Root, arr1Num, arr1NumLen, 1);
  DrawInConsole(p1Root);
  // PreorderTraversal(p1Root);
  // InorderTraversal(p1Root);
  // SubsequentTraversal(p1Root);
  //
  // printf("GetDepth: %d\r\n", GetDepth(p1Root));
  //
  // BreadthFirstSearch(p1Root);
  // DepthFirstSearch(p1Root);
}
