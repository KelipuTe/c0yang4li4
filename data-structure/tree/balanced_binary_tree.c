#include <math.h>
#include <stdio.h>
#include <stdlib.h>

// ## 平衡二叉树（AVL Tree） ##
// 平衡二叉树是一种特殊的二叉排序树

// 平衡二叉树结点
typedef struct BalancedBinaryTreeNode {
  // 结点值
  int num;
  // 指向左子树的根结点
  struct BalancedBinaryTreeNode *p1Left;
  // 指向右子树的根结点
  struct BalancedBinaryTreeNode *p1Right;
  // 指向父结点
  struct BalancedBinaryTreeNode *p1Prev;
  // 结点深度，最下层叶子结点的深度约定为 1，从下层往上层，每层依次 +1。
  // 结点平衡值，左右子树根结点深度的差值，如果算出来是 -1、0、1，则结点是平衡的。
  int depth;
} BalancedBinaryTreeNode;

// BalancedBinaryTreeNode **，指向二叉树的，指向左子树的根结点的指针或者指向右子树的根结点的指针，的指针
// BalancedBinaryTreeNode **，指向，指向根结点的指针，的指针
extern void AddNode(BalancedBinaryTreeNode **, int, BalancedBinaryTreeNode **);
// 计算结点深度
int getDepth(BalancedBinaryTreeNode *);
// 计算结点平衡值
int getBalance(BalancedBinaryTreeNode *);
// 左旋
void leftRotate(BalancedBinaryTreeNode *, BalancedBinaryTreeNode **);
// 右旋
void rightRotate(BalancedBinaryTreeNode *, BalancedBinaryTreeNode **);
// 中序遍历，左根右
// BalancedBinaryTreeNode *，指向根结点
extern void InorderTraversal(BalancedBinaryTreeNode *);
void doInorderTraversal(BalancedBinaryTreeNode *);

void AddNode(BalancedBinaryTreeNode **p2Node, int num, BalancedBinaryTreeNode **p2Root) {
  // 临时，存储结点平衡值
  int t1Balance = 0;

  // 没有结点时，初始化结点
  if (NULL == *p2Node) {
    *p2Node = (BalancedBinaryTreeNode *)malloc(sizeof(BalancedBinaryTreeNode));
    (*p2Node)->num = num;
    (*p2Node)->p1Left = NULL;
    (*p2Node)->p1Right = NULL;
    (*p2Node)->p1Prev = NULL;
    (*p2Node)->depth = 1;
    return;
  }

  // 有根结点时，寻找插入插入值的位置
  if (num < (*p2Node)->num) {
    // 插入值小于结点值，去左子树继续查询
    if (NULL == (*p2Node)->p1Left) {
      // 如果左子树不存在，则插入值就插到这个位置
      (*p2Node)->p1Left = (BalancedBinaryTreeNode *)malloc(sizeof(BalancedBinaryTreeNode));
      (*p2Node)->p1Left->num = num;
      (*p2Node)->p1Left->p1Left = NULL;
      (*p2Node)->p1Left->p1Right = NULL;
      (*p2Node)->p1Left->p1Prev = *p2Node;
      (*p2Node)->p1Left->depth = 1;
    } else {
      // 如果左子树存在，就在左子树中继续寻找插入插入值的位置
      AddNode(&((*p2Node)->p1Left), num, p2Root);
    }
  } else if (num > (*p2Node)->num) {
    // 插入值大于结点值，去右子树继续查询
    if (NULL == (*p2Node)->p1Right) {
      (*p2Node)->p1Right = (BalancedBinaryTreeNode *)malloc(sizeof(BalancedBinaryTreeNode));
      (*p2Node)->p1Right->num = num;
      (*p2Node)->p1Right->p1Left = NULL;
      (*p2Node)->p1Right->p1Right = NULL;
      (*p2Node)->p1Right->p1Prev = *p2Node;
      (*p2Node)->p1Right->depth = 1;
    } else {
      // 如果右子树存在，就在右子树中继续寻找插入插入值的位置
      AddNode(&((*p2Node)->p1Right), num, p2Root);
    }
  } else {
    // 插入值已经存在，什么都不用做
    return;
  }
  // 计算结点平衡，看看需不需要旋转
  t1Balance = getBalance(*p2Node);
  if (t1Balance < -1) {
    // 右子树高
    if (getBalance((*p2Node)->p1Right) == 1) {
      // RL 型，右子结点的左子树比右子树高。
      // 这种情况如果直接左旋，还是会不平衡。需要先在右子结点上右旋，变成 RR 型。
      rightRotate((*p2Node)->p1Right, p2Root);
    }
    // RR 型，右子结点的右子树比左子树高，可以直接左旋。
    leftRotate(*p2Node, p2Root);
  } else if (t1Balance > 1) {
    // 左子树高
    if (getBalance((*p2Node)->p1Left) == -1) {
      // LR 型，左子结点的右子树比左子树高。
      // 这种情况如果直接右旋，还是会不平衡。需要先在左子结点上左旋，变成 LL 型。
      leftRotate((*p2Node)->p1Left, p2Root);
    }
    // LL 型，左子结点的左子树比右子树高，可以直接右旋。
    rightRotate(*p2Node, p2Root);
  }
  // 重新计算自己的结点深度
  (*p2Node)->depth = getDepth(*p2Node);
}

int getDepth(BalancedBinaryTreeNode *p1Node) {
  int depthL = 0;
  int depthR = 0;
  if (p1Node->p1Left != NULL) {
    depthL = p1Node->p1Left->depth;
  }
  if (p1Node->p1Right != NULL) {
    depthR = p1Node->p1Right->depth;
  }
  return (int)fmax(depthL, depthR) + 1;
}

int getBalance(BalancedBinaryTreeNode *p1Node) {
  int depthL = 0;
  int depthR = 0;
  if (p1Node->p1Left != NULL) {
    depthL = p1Node->p1Left->depth;
  }
  if (p1Node->p1Right != NULL) {
    depthR = p1Node->p1Right->depth;
  }
  return depthL - depthR;
}

void leftRotate(BalancedBinaryTreeNode *p1Node, BalancedBinaryTreeNode **p2Root) {
  // 自己的父结点（SF）
  BalancedBinaryTreeNode *p1Prev = p1Node->p1Prev;
  // 自己的右子结点（SR），左旋时，这个结点一定有
  BalancedBinaryTreeNode *p1Right = p1Node->p1Right;
  // 自己的右子结点的左子结点（SRL），这个结点不一定有
  BalancedBinaryTreeNode *p1RightLeft = p1Node->p1Right->p1Left;

  // 如果自己的是根结点，那么自己的右子结点变成新的根结点
  if (p1Node == *p2Root) {
    *p2Root = p1Right;
  }
  // 自己的右子结点（SR）变成自己的父结点
  // 自己的变成的自己的右子结点（SR）的左子结点
  p1Node->p1Right = NULL;
  p1Node->p1Prev = p1Right;
  p1Right->p1Left = p1Node;
  p1Right->p1Prev = p1Prev;
  // 如果自己有父节点（SF），把自己的右子结点（SR）接到父节点（SF）的对应位置。
  if (p1Prev != NULL) {
    if (p1Node == p1Prev->p1Left) {
      p1Prev->p1Left = p1Right;
    } else if (p1Node == p1Prev->p1Right) {
      p1Prev->p1Right = p1Right;
    }
  }
  // 如果自己的右子结点（SR）有左子结点（SRL），要把自己的右子结点（SR）的左子结点（SRL）变成自己的右子结点
  p1Node->p1Right = p1RightLeft;
  if (p1RightLeft != NULL) {
    p1RightLeft->p1Prev = p1Node;
  }
  // 重新计算自己和的右子结点（SR）的结点深度
  p1Node->depth = getDepth(p1Node);
  p1Right->depth = getDepth(p1Right);
}

void rightRotate(BalancedBinaryTreeNode *p1Node, BalancedBinaryTreeNode **p2Root) {
  // 自己的父结点（SF）
  BalancedBinaryTreeNode *p1Prev = p1Node->p1Prev;
  // 自己的左子结点（SL），右旋时，这个结点一定有
  BalancedBinaryTreeNode *p1Left = p1Node->p1Left;
  // 自己的左子结点的右子结点（SLR），这个结点不一定有
  BalancedBinaryTreeNode *p1LeftRight = p1Node->p1Left->p1Right;

  // 如果自己的是根结点，那么自己的左子结点变成新的根结点
  if (p1Node == *p2Root) {
    *p2Root = p1Left;
  }
  // 自己的左子结点（SL）变成自己的父结点
  // 自己的变成的自己的左子结点（SL）的右子结点
  p1Node->p1Left = NULL;
  p1Node->p1Prev = p1Left;
  p1Left->p1Right = p1Node;
  p1Left->p1Prev = p1Prev;
  // 如果自己有父节点（SF），把自己的左子结点（SL）接到父节点（SF）的对应位置。
  if (p1Prev != NULL) {
    if (p1Node == p1Prev->p1Left) {
      p1Prev->p1Left = p1Left;
    } else if (p1Node == p1Prev->p1Right) {
      p1Prev->p1Right = p1Left;
    }
  }
  // 如果自己的左子结点（SL）有右子结点（SLR），要把自己的左子结点（SL）的右子结点（SLR）变成自己的右子结点
  p1Node->p1Right = p1LeftRight;
  if (p1LeftRight != NULL) {
    p1LeftRight->p1Prev = p1Node;
  }
  // 重新计算自己和的左子结点（SL）的结点深度
  p1Node->depth = getDepth(p1Node);
  p1Left->depth = getDepth(p1Left);
}

void InorderTraversal(BalancedBinaryTreeNode *p1Root) {
  printf("InorderTraversal: ");
  doInorderTraversal(p1Root);
  printf("\r\n");
}

void doInorderTraversal(BalancedBinaryTreeNode *p1Root) {
  BalancedBinaryTreeNode *p1t1Root = p1Root;
  if (p1t1Root == NULL) {
    return;
  }

  doInorderTraversal(p1t1Root->p1Left);
  printf("%d,", p1t1Root->num);
  doInorderTraversal(p1t1Root->p1Right);
}
