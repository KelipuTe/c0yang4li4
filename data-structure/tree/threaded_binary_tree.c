#include <stdio.h>
#include <stdlib.h>

// ## 线索二叉树 ##

// 用于标记无效的结点 2147483648 = $2^{31}$
#define UNDEFINED_NODE_VALUE (-2147483648)

#define TAG_UNDEFINED 0
#define TAG_CHILD 1
#define TAG_THREAD 2

// 线索二叉树结点
typedef struct ThreadedBinaryTreeNode {
  // 结点值
  int num;
  // 指向左子树的根结点
  struct ThreadedBinaryTreeNode *p1Left;
  // 指向右子树的根结点
  struct ThreadedBinaryTreeNode *p1Right;
  // 左标记，TAG_UNDEFINED=未设置；TAG_CHILD=左子树根结点；TAG_THREAD=前驱线索
  int8_t leftTag;
  // 右标记，TAG_UNDEFINED=未设置；TAG_CHILD=右子树根结点；TAG_THREAD=后继线索
  int8_t rightTag;
} ThreadedBinaryTreeNode;

extern void BuildBinaryTreeFromArray(ThreadedBinaryTreeNode **, int *, int, int, ThreadedBinaryTreeNode *);
extern void InorderTraversal(ThreadedBinaryTreeNode *);
void doInorderTraversal(ThreadedBinaryTreeNode *);
extern void InorderThreaded(ThreadedBinaryTreeNode *, ThreadedBinaryTreeNode **);

/**
 * 从数组构造二叉树
 * @param p2Node 指向二叉树的，指向左子树的根结点的指针或者指向右子树的根结点的指针，的指针
 * @param p1arr1Num
 * @param arr1NumLen
 * @param index
 * @param p1Prev 指向前驱结点的指针
 */
void BuildBinaryTreeFromArray(ThreadedBinaryTreeNode **p2Node, int *p1arr1Num, int arr1NumLen, int index, ThreadedBinaryTreeNode *p1Prev) {
  if (index >= arr1NumLen) {
    return;
  }
  if (p1arr1Num[index] == UNDEFINED_NODE_VALUE) {
    *p2Node = NULL;
  } else {
    *p2Node = (ThreadedBinaryTreeNode *)malloc(sizeof(ThreadedBinaryTreeNode));
    (*p2Node)->num = p1arr1Num[index];
    (*p2Node)->p1Left = NULL;
    (*p2Node)->p1Right = NULL;
    (*p2Node)->leftTag = TAG_UNDEFINED;
    (*p2Node)->rightTag = TAG_UNDEFINED;
    // 给父结点作标记
    if (p1Prev != NULL) {
      if (p1Prev->p1Left == *p2Node) {
        p1Prev->leftTag = TAG_CHILD;
      } else if (p1Prev->p1Right == *p2Node) {
        p1Prev->rightTag = TAG_CHILD;
      }
    }
    BuildBinaryTreeFromArray(&((*p2Node)->p1Left), p1arr1Num, arr1NumLen, index * 2, *p2Node);
    BuildBinaryTreeFromArray(&((*p2Node)->p1Right), p1arr1Num, arr1NumLen, index * 2 + 1, *p2Node);
  }
}

/**
 * 中序遍历，左根右
 * @param p1Root 指向根结点
 */
void InorderTraversal(ThreadedBinaryTreeNode *p1Root) {
  printf("InorderTraversal: ");
  doInorderTraversal(p1Root);
  printf("\r\n");
}

void doInorderTraversal(ThreadedBinaryTreeNode *p1Node) {
  if (NULL == p1Node) {
    return;
  }

  if (TAG_CHILD == p1Node->leftTag) {
    doInorderTraversal(p1Node->p1Left);
  }
  printf("%d,", p1Node->num);
  if (TAG_CHILD == p1Node->rightTag) {
    doInorderTraversal(p1Node->p1Right);
  }
}

/**
 * 中序遍历线索化
 * @param p1Node 指向根结点
 * @param p2Prev 指向，指向前驱结点的指针，的指针
 */
void InorderThreaded(ThreadedBinaryTreeNode *p1Node, ThreadedBinaryTreeNode **p2Prev) {
  if (NULL == p1Node) {
    return;
  }

  if (TAG_CHILD == p1Node->leftTag) {
    // 有左子树
    InorderThreaded(p1Node->p1Left, p2Prev);
  } else if (TAG_UNDEFINED == p1Node->leftTag) {
    if (*p2Prev != NULL) {
      p1Node->leftTag = TAG_THREAD;
      p1Node->p1Left = *p2Prev;
    }
  }

  // 如果前驱结点没有右子树，就设置后继线索
  if (*p2Prev != NULL && TAG_UNDEFINED == (*p2Prev)->rightTag) {
    (*p2Prev)->rightTag = TAG_THREAD;
    (*p2Prev)->p1Right = p1Node;
  }
  // 登记自己为新的前驱结点
  *p2Prev = p1Node;

  if (TAG_CHILD == p1Node->rightTag) {
    // 有右子树
    InorderThreaded(p1Node->p1Right, p2Prev);
  }
}
