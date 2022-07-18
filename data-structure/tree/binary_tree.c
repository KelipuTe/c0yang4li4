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
  // 指向左子树的根结点
  struct BinaryTreeNode *p1Left;
  // 指向右子树的根结点
  struct BinaryTreeNode *p1Right;
} BinaryTreeNode;

// 从数组构造二叉树
// BinaryTreeNode **，指向二叉树的，指向左子树的根结点的指针或者指向右子树的根结点的指针，的指针
extern void BuildBinaryTreeFromArray(BinaryTreeNode **, int *, int, int);
// 前序遍历，根左右
// BinaryTreeNode *，指向根结点
extern void PreorderTraversal(BinaryTreeNode *);
void doPreorderTraversal(BinaryTreeNode *);
// 中序遍历，左根右
// BinaryTreeNode *，指向根结点
extern void InorderTraversal(BinaryTreeNode *);
void doInorderTraversal(BinaryTreeNode *);
// 后序遍历，左右根
// BinaryTreeNode *，指向根结点
extern void SubsequentTraversal(BinaryTreeNode *);
void doSubsequentTraversal(BinaryTreeNode *);
// 计算二叉树深度
// BinaryTreeNode *，指向根结点
extern int GetDepth(BinaryTreeNode *);
// 广度优先遍历
// BinaryTreeNode *，指向根结点
extern void BreadthFirstSearch(BinaryTreeNode *);
void doBreadthFirstSearch(BinaryTreeNode *);
// 深度优先遍历
// BinaryTreeNode *，指向根结点
extern void DepthFirstSearch(BinaryTreeNode *);
void doDepthFirstSearch(BinaryTreeNode *);

void BuildBinaryTreeFromArray(BinaryTreeNode **p2Root, int *p1arr1Num, int arr1NumLen, int index) {
  // 用数组保存的二叉树结构。
  // 先用无效结点把二叉树补成完全二叉树。深度为 n 的二叉树需要的数组大小为 2^(n)-1。
  // 从数组下标为 1 的位置开始存放二叉树的结点（下标为 0 的位置可以放二叉树的总结点数），顺序是从上到下从左到右。
  // 这样，下标为 n 的结点的，左子树的根结点下标为 2*n，右子树的根结点下标为 2*n+1，父结点的下标是 i/2 向下取整。
  if (index >= arr1NumLen) {
    return;
  }
  if (p1arr1Num[index] == UNDEFINED_NODE_VALUE) {
    // 如果数组中这个位置是无效值，则不构造这个结点
    *p2Root = NULL;
  } else {
    // 如果数组中这个位置是有效值，则构造这个结点
    *p2Root = (BinaryTreeNode *)malloc(sizeof(BinaryTreeNode));
    (*p2Root)->num = p1arr1Num[index];
    (*p2Root)->p1Left = NULL;
    (*p2Root)->p1Right = NULL;

    // 用数组保存二叉树结构时，二叉树结点与子结点的关系可以通过数组下标体现
    // 这里把这次构造的结点的左右结点传递下去，用递归的方式分别构造左右子树
    BuildBinaryTreeFromArray(&((*p2Root)->p1Left), p1arr1Num, arr1NumLen, index * 2);
    BuildBinaryTreeFromArray(&((*p2Root)->p1Right), p1arr1Num, arr1NumLen, index * 2 + 1);
  }
}

void PreorderTraversal(BinaryTreeNode *p1Root) {
  printf("PreorderTraversal: ");
  doPreorderTraversal(p1Root);
  printf("\r\n");
}

void doPreorderTraversal(BinaryTreeNode *p1Root) {
  BinaryTreeNode *p1t1Root = p1Root;
  if (p1t1Root == NULL) {
    return;
  }

  printf("%d,", p1t1Root->num);
  doPreorderTraversal(p1t1Root->p1Left);
  doPreorderTraversal(p1t1Root->p1Right);
}

void InorderTraversal(BinaryTreeNode *p1Root) {
  printf("InorderTraversal: ");
  doInorderTraversal(p1Root);
  printf("\r\n");
}

void doInorderTraversal(BinaryTreeNode *p1Root) {
  BinaryTreeNode *p1t1Root = p1Root;
  if (p1t1Root == NULL) {
    return;
  }

  doInorderTraversal(p1t1Root->p1Left);
  printf("%d,", p1t1Root->num);
  doInorderTraversal(p1t1Root->p1Right);
}

void SubsequentTraversal(BinaryTreeNode *p1Root) {
  printf("SubsequentTraversal: ");
  doSubsequentTraversal(p1Root);
  printf("\r\n");
}

void doSubsequentTraversal(BinaryTreeNode *p1Root) {
  BinaryTreeNode *p1t1Root = p1Root;
  if (p1t1Root == NULL) {
    return;
  }

  doSubsequentTraversal(p1t1Root->p1Left);
  doSubsequentTraversal(p1t1Root->p1Right);
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
  printf("BreadthFirstSearch: ");
  doBreadthFirstSearch(p1Root);
  printf("\r\n");
}

void doBreadthFirstSearch(BinaryTreeNode *p1Root) {
  // 广度优先遍历需要借助队列存储结构
  // 队列
  BinaryTreeNode *arr1Queue[100];
  // 队列头，队列尾
  int queueHead = 0, queueTail = 0;
  // 当前遍历的层；当前层的最后一个结点在队列中的下标
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
      if (t1Node->p1Left != NULL) {
        // 左结点先入队，先遍历
        arr1Queue[queueTail++] = t1Node->p1Left;
      }
      if (t1Node->p1Right != NULL) {
        // 右结点后入队，后遍历
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
    // 层数 + 1
    tierNum++;
  }
}

void DepthFirstSearch(BinaryTreeNode *p1Root) {
  printf("DepthFirstSearch: ");
  doDepthFirstSearch(p1Root);
  printf("\r\n");
}

void doDepthFirstSearch(BinaryTreeNode *p1Root) {
  // 广度优先遍历需要借助栈存储结构
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
