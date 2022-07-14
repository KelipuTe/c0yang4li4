#include <math.h>
#include <stdio.h>
#include <stdlib.h>

/* ## 二叉树 ## */

// 用于标记无效的结点 2147483648 = $2^{31}$
#define UNDEFINED_NODE_VALUE (-2147483648)

// 二叉树结点
typedef struct BinaryTreeNode {
  // 结点值
  int num;
  // 左子树的根结点
  struct BinaryTreeNode *p1Left;
  // 右子树的根结点
  struct BinaryTreeNode *p1Right;
} BinaryTreeNode;

// 从数组构造二叉树
extern void BuildBinaryTreeFromArray(BinaryTreeNode **, int *, int, int);
// 前序遍历，根左右
extern void PreorderTraversal(BinaryTreeNode *);
// 中序遍历，左根右
extern void InorderTraversal(BinaryTreeNode *);
// 后序遍历，左右根
extern void SubsequentTraversal(BinaryTreeNode *);
// 计算二叉树深度
extern int GetDepth(BinaryTreeNode *);

int main() {
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

  return 0;
}

void BuildBinaryTreeFromArray(BinaryTreeNode **p2Root, int *p1arr1Num, int arr1NumLen, int index) {
  if (index <= arr1NumLen) {
    if (p1arr1Num[index - 1] == UNDEFINED_NODE_VALUE) {
      // 如果数组中这个位置是无效值，则不构造这个结点
      *p2Root = NULL;
    } else {
      // 如果数组中这个位置是有效值，则构造这个结点
      *p2Root = (BinaryTreeNode *)malloc(sizeof(BinaryTreeNode));
      (*p2Root)->num = p1arr1Num[index - 1];
      (*p2Root)->p1Left = NULL;
      (*p2Root)->p1Right = NULL;

      // 用数组保存二叉树结构时，二叉树结点与子结点的关系可以通过数组下标体现
      // 这里把这次构造的结点的左右结点传递下去，用递归的方式分别构造左右子树
      BuildBinaryTreeFromArray(&((*p2Root)->p1Left), p1arr1Num, arr1NumLen, index * 2);
      BuildBinaryTreeFromArray(&((*p2Root)->p1Right), p1arr1Num, arr1NumLen, index * 2 + 1);
    }
  }
}

void PreorderTraversal(BinaryTreeNode *p1Root) {
  BinaryTreeNode *p1t1Root = p1Root;
  if (p1t1Root == NULL) {
    return;
  }

  printf("%d,", p1t1Root->num);
  PreorderTraversal(p1t1Root->p1Left);
  PreorderTraversal(p1t1Root->p1Right);
}

extern void InorderTraversal(BinaryTreeNode *p1Root) {
  BinaryTreeNode *p1t1Root = p1Root;
  if (p1t1Root == NULL) {
    return;
  }

  PreorderTraversal(p1t1Root->p1Left);
  printf("%d,", p1t1Root->num);
  PreorderTraversal(p1t1Root->p1Right);
}

extern void SubsequentTraversal(BinaryTreeNode *p1Root) {
  BinaryTreeNode *p1t1Root = p1Root;
  if (p1t1Root == NULL) {
    return;
  }

  PreorderTraversal(p1t1Root->p1Left);
  PreorderTraversal(p1t1Root->p1Right);
  printf("%d,", p1t1Root->num);
}

int GetDepth(BinaryTreeNode *p1Root) {
  int leftDepth = 0, rightDepth = 0;

  if (p1Root == NULL) {
    return 0;
  }

  leftDepth = GetDepth(p1Root->p1Left);
  rightDepth = GetDepth(p1Root->p1Right);
  return (int)fmax(leftDepth, rightDepth) + 1;
}
