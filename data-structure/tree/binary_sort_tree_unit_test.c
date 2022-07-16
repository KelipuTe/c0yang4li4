#include "binary_sort_tree.c"

int main() {
  // 根结点指针
  BinaryTreeNode *p1Root = NULL;

  int arr1[10]={55,60,11,88,27,54,74,11,69,19};
  int arr1Len = 10;

  for (int i = 0; i < arr1Len; i++) {
    AddNode(&p1Root, arr1[i]);
  }

  InorderTraversal(p1Root);

  DeleteNode(p1Root, arr1[4]);

  InorderTraversal(p1Root);

  return 0;
}