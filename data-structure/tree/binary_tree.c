#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "../queue/linked_list_queue.c"

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
// 广度优先遍历
extern void BreadthFirstSearch(BinaryTreeNode *);
// 深度优先遍历
extern void DepthFirstSearch(BinaryTreeNode *);

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

void BreadthFirstSearch(BinaryTreeNode *p1Root) {
  // 队列
  BinaryTreeNode *arr1Queue[100];
  // 队列头尾
  int queueHead = 0, queueTail = 0;
  // 当前遍历的层，当前层的最后一个结点在队列中的下标
  int tierNum = 1, tierTail = 0;
  BinaryTreeNode *t1Node;

  arr1Queue[queueTail++] = p1Root;
  t1Node = arr1Queue[queueHead++];
  // 持续遍历，直到队列为空
  while (queueHead <= queueTail && t1Node != NULL) {
    // 遍历当前遍历的层中的结点
    tierTail = queueTail;
    while (queueHead <= tierTail) {
      printf("%d-%d,", tierNum, t1Node->num);
      // 左结点先入队，先遍历
      if (t1Node->p1Left != NULL) {
        arr1Queue[queueTail++] = t1Node->p1Left;
      }
      // 右结点后入队，后遍历
      if (t1Node->p1Right != NULL) {
        arr1Queue[queueTail++] = t1Node->p1Right;
      }
      if (queueHead < queueTail) {
        t1Node = arr1Queue[queueHead++];
      } else {
        // 控制外层遍历结束条件
        queueHead = queueTail + 1;
        t1Node = NULL;
      }
    }
    tierNum++;
  }
}

void DepthFirstSearch(BinaryTreeNode *p1Root) {
  // 栈
  BinaryTreeNode *arr1Stark[100];
  // 栈顶
  int top = 0;
  BinaryTreeNode *t1Node;

  arr1Stark[top++] = p1Root;
  t1Node = arr1Stark[--top];
  // 持续遍历，直到栈为空
  while (top >= 0 && t1Node != NULL) {
    printf("%d,", t1Node->num);
    if (t1Node->p1Right != NULL) {
      // 右结点先入栈，后遍历
      arr1Stark[top++] = t1Node->p1Right;
    }
    if (t1Node->p1Left != NULL) {
      // 左结点后入栈，先遍历
      arr1Stark[top++] = t1Node->p1Left;
    }
    if (top > 0) {
      t1Node = arr1Stark[--top];
    } else {
      t1Node = NULL;
    }
  }
}
