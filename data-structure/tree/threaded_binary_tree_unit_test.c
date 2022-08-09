#include "threaded_binary_tree.c"

int main() {
  // 指向根结点
  ThreadedBinaryTreeNode *p1Root = NULL;
  // 临时，线索化时，指向前驱结点
  ThreadedBinaryTreeNode *p1t1Prev = NULL;

  int arr1Num[] = {UNDEFINED_NODE_VALUE, 1, 2, 3, 4, 5, 6, 7, UNDEFINED_NODE_VALUE, UNDEFINED_NODE_VALUE, 10, 11};
  int arr1NumLen = (sizeof(arr1Num) / sizeof(int));

  BuildBinaryTreeFromArray(&p1Root, arr1Num, arr1NumLen, 1, NULL);

  InorderTraversal(p1Root);
  InorderThreaded(p1Root, &p1t1Prev);
  return 0;
}
