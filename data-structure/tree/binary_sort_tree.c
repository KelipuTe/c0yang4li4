#include <stdlib.h>

#include "binary_tree.c"

// ## 二叉排序树 ##

// 插入结点
// BinaryTreeNode **，指向二叉树的，指向左子树的根结点的指针或者指向右子树的根结点的指针，的指针
extern void AddNode(BinaryTreeNode **, int);
// 删除结点
// BinaryTreeNode *，指向根结点
extern void DeleteNode(BinaryTreeNode *, int);

void AddNode(BinaryTreeNode **p2Node, int num) {
  // 记录要插入的结点的父结点
  BinaryTreeNode *p1Prev = NULL;
  // 临时变量，用于遍历
  BinaryTreeNode *p1t1Node = NULL;
  // 是否需要插入新结点，默认需要插入
  int isNeedAdd = 1;

  // 没有结点时，初始化结点
  if (NULL == *p2Node) {
    *p2Node = (BinaryTreeNode *)malloc(sizeof(BinaryTreeNode));
    (*p2Node)->num = num;
    (*p2Node)->p1Left = NULL;
    (*p2Node)->p1Right = NULL;
    return;
  }

  // 有根结点时，寻找插入插入值的位置

  // 查询的逻辑
  p1Prev = *p2Node;
  p1t1Node = *p2Node;
  while (p1t1Node != NULL) {
    if (num < p1t1Node->num) {
      // 插入值小于结点值，去左子树继续查询
      p1Prev = p1t1Node;
      p1t1Node = p1t1Node->p1Left;
    } else if (num > p1t1Node->num) {
      // 插入值大于结点值，去右子树继续查询
      p1Prev = p1t1Node;
      p1t1Node = p1t1Node->p1Right;
    } else {
      // 插入值等于结点值，什么也不做
      isNeedAdd = 0;
      break;
    }
  }

  // 添加结点的逻辑
  if (0 == isNeedAdd) {
    return;
  }
  // 如果需要插入新结点
  // p1Prev 会指向将要插入的结点的父结点，p1t1Node 会指向 NULL
  p1t1Node = (BinaryTreeNode *)malloc(sizeof(BinaryTreeNode));
  p1t1Node->num = num;
  p1t1Node->p1Left = NULL;
  p1t1Node->p1Right = NULL;
  // 比较一下结点应该插到哪一边
  if (num < p1Prev->num) {
    p1Prev->p1Left = p1t1Node;
  } else if (num > p1Prev->num) {
    p1Prev->p1Right = p1t1Node;
  }
}

void DeleteNode(BinaryTreeNode *p1Root, int num) {
  // 要删除的结点的父结点
  BinaryTreeNode *p1Prev = NULL;
  // 要删除的结点
  BinaryTreeNode *p1Delete = NULL;
  // 临时变量，用于遍历
  BinaryTreeNode *p1t1Node = NULL;

  // 查询的逻辑
  p1t1Node = p1Root;
  while (p1t1Node != NULL) {
    if (num < p1t1Node->num) {
      // 删除值小于结点值，去左子树继续查询
      p1Prev = p1t1Node;
      p1t1Node = p1t1Node->p1Left;
    } else if (num > p1t1Node->num) {
      // 删除值大于结点值，去右子树继续查询
      p1Prev = p1t1Node;
      p1t1Node = p1t1Node->p1Right;
    } else {
      // 删除值等于结点值，要删除的结点（DEL）
      p1Delete = p1t1Node;
      break;
    }
  }

  // 删除结点的逻辑
  if (NULL == p1Delete) {
    return;
  }
  if (NULL == p1Delete->p1Left) {
    // 如果要删除的结点的左子树为空
    // 直接把要删除的结点的右子树，接到要删除的结点的父结点的对应位置
    if (p1Delete == p1Prev->p1Left) {
      p1Prev->p1Left = p1Delete->p1Right;
    } else if (p1Delete == p1Prev->p1Right) {
      p1Prev->p1Right = p1Delete->p1Right;
    }
    free(p1Delete);
  } else if (NULL == p1Delete->p1Right) {
    // 如果要删除的结点的右子树为空
    // 直接把要删除的结点的左子树，接到要删除的结点的父结点的对应位置
    if (p1Delete == p1Prev->p1Left) {
      p1Prev->p1Left = p1Delete->p1Left;
    } else if (p1Delete == p1Prev->p1Right) {
      p1Prev->p1Right = p1Delete->p1Left;
    }
    free(p1Delete);
  } else {
    // 如果要删除的结点的左子树和右子树都存在
    // 可以从左子树中找到结点值最大的结点，替代被删除的结点
    // 也可以从右子树中找到结点值最小的结点，替代被删除的结点
    p1Prev = p1Delete;
    p1t1Node = p1Delete->p1Left;
    while (p1t1Node->p1Right != NULL) {
      p1Prev = p1t1Node;
      p1t1Node = p1t1Node->p1Right;
    }
    // 到此 p1t1Node 就是要删除的结点的左子树中结点值最大的结点
    // 直接把左子树中结点值最大的结点的结点值赋值到要删除的结点上
    p1Delete->num = p1t1Node->num;
    if (p1Prev != p1Delete) {
      // 如果左子树中结点值最大的结点的父结点（A），不是要删除的结点（DEL），则要删除结点的左子结点（AL）有右子结点（ALB）
      // 需要把上述右子结点（ALB）的左子树，接到左子树中结点值最大的结点的父结点（A）的右子树的位置
      // 这里不用考虑上述右子结点的右子树，因为逻辑上不会出现这种情况
      p1Prev->p1Right = p1t1Node->p1Left;
    } else {
      // 如果左子树中结点值最大的结点的父结点（A），就是要删除的结点（DEL），则要删除结点的左子结点（AL）没有右子结点（ALB）
      // 直接把该左子结点（AL）的左子树，接到左子树中结点值最大的结点的父结点（A）的左子树的位置
      p1Prev->p1Left = p1t1Node->p1Left;
    }
    // 释放掉结点值最大的结点，这个结点的值已经被记录到原先要删除的结点了
    free(p1t1Node);
  }
}
