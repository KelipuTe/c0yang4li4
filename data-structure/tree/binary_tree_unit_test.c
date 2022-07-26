#include "binary_tree.c"

void BinaryTreeUnitTesting();

int main() {

  BinaryTreeUnitTesting();
  return 0;
}

/**
 * 单元测试
 */
void BinaryTreeUnitTesting() {
  PrintDefine();

  // 指向根结点
  BinaryTreeNode *p1Root = NULL;

  int arr1Num[] = {70,
                   1, 2, 3, 4, 5, 6, 7, 8, 9, 10, INT_MIN, INT_MIN, INT_MIN, 14, 15,
                   16, INT_MIN, 18, 19, 20, 21, INT_MIN, INT_MIN, INT_MIN, INT_MIN, INT_MIN, INT_MIN, 28, 29, 30, 31};
                   // 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47,
                   // 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63,
                   // 64, 65, 66, 67, 68, 69, 70};
  int arr1NumLen = (sizeof(arr1Num) / sizeof(int));

  BuildBinaryTreeFromArray(&p1Root, arr1Num, arr1NumLen, 1);

  DrawInConsole(p1Root);

  PreorderTraversal(p1Root);
  InorderTraversal(p1Root);
  SubsequentTraversal(p1Root);

  printf("GetDepth: %d\r\n", GetDepth(p1Root));

  BreadthFirstSearch(p1Root);
  DepthFirstSearch(p1Root);
}
