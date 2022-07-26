#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ## 平衡二叉树（AVL Tree） ##
// 平衡二叉树是一种特殊的二叉排序树

// 用极值标记无效的结点
#define INT_MIN (1 << 31)
#define INT_MAX (-((1 << 31) + 1))

// 二叉树最大层数
#define TIER_NUM_MAX 8
// 最下层最大结点数
#define TIER_NODE_NUM_MAX (1 << (TIER_NUM_MAX - 1))
// 二叉树最大结点数
#define TREE_NODE_NUM_MAX ((1 << TIER_NUM_MAX) - 1)

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

extern void AddNode(BalancedBinaryTreeNode **, int);
extern void DrawInConsole(BalancedBinaryTreeNode *);
int getDepthForBalance(BalancedBinaryTreeNode *);
int getBalance(BalancedBinaryTreeNode *);
void leftRotate(BalancedBinaryTreeNode *, BalancedBinaryTreeNode **);
void rightRotate(BalancedBinaryTreeNode *, BalancedBinaryTreeNode **);
extern void InorderTraversal(BalancedBinaryTreeNode *);
void doInorderTraversal(BalancedBinaryTreeNode *);
extern int GetDepth(BalancedBinaryTreeNode *);

/**
 * 添加结点
 * @param p2Root 指向，指向二叉树的根结点的指针，的指针
 * @param num
 */
void AddNode(BalancedBinaryTreeNode **p2Root, int num) {
  printf("AddNode: %d\r\n", num);

  // 记录要插入的结点的父结点
  BalancedBinaryTreeNode *p1Prev = NULL;
  // 临时，用于遍历
  BalancedBinaryTreeNode *p1t1Node = NULL;
  // 是否需要插入新结点，默认需要插入
  int isNeedAdd = 1;
  // 临时，存储结点平衡值
  int t1Balance = 0;

  // 没有根结点时，初始化结点
  if (NULL == *p2Root) {
    *p2Root = (BalancedBinaryTreeNode *)malloc(sizeof(BalancedBinaryTreeNode));
    (*p2Root)->num = num;
    (*p2Root)->p1Left = NULL;
    (*p2Root)->p1Right = NULL;
    (*p2Root)->p1Prev = NULL;
    (*p2Root)->depth = 1;
    return;
  }

  // 有结点时，寻找插入插入值的位置

  // 查询的逻辑
  p1Prev = *p2Root;
  p1t1Node = *p2Root;
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
  p1t1Node = (BalancedBinaryTreeNode *)malloc(sizeof(BalancedBinaryTreeNode));
  p1t1Node->num = num;
  p1t1Node->p1Left = NULL;
  p1t1Node->p1Right = NULL;
  p1t1Node->p1Prev = p1Prev;
  p1t1Node->depth = 1;
  // 比较一下结点应该插到哪一边
  if (num < p1Prev->num) {
    p1Prev->p1Left = p1t1Node;
  } else if (num > p1Prev->num) {
    p1Prev->p1Right = p1t1Node;
  }

  DrawInConsole(*p2Root);

  // 从插入的新结点的父结点开始，一层一层往上，重新计算平衡值
  while (p1Prev != NULL) {
    // 计算结点平衡，看看需不需要旋转
    t1Balance = getBalance(p1Prev);
    if (t1Balance < -1) {
      // 右子树高
      if (getBalance(p1Prev->p1Right) == 1) {
        // RL 型，右子结点的左子树比右子树高。
        // 这种情况如果直接左旋，还是会不平衡。需要先在右子结点上右旋，变成 RR 型。
        rightRotate(p1Prev->p1Right, p2Root);
      }
      // RR 型，右子结点的右子树比左子树高，可以直接左旋。
      leftRotate(p1Prev, p2Root);
    } else if (t1Balance > 1) {
      // 左子树高
      if (getBalance(p1Prev->p1Left) == -1) {
        // LR 型，左子结点的右子树比左子树高。
        // 这种情况如果直接右旋，还是会不平衡。需要先在左子结点上左旋，变成 LL 型。
        leftRotate(p1Prev->p1Left, p2Root);
      }
      // LL 型，左子结点的左子树比右子树高，可以直接右旋。
      rightRotate(p1Prev, p2Root);
    }
    // 重新计算自己的结点深度
    p1Prev->depth = getDepthForBalance(p1Prev);
    p1Prev = p1Prev->p1Prev;
  }
}

/**
 * 在控制台输出二叉树，需要借助层次遍历的逻辑
 * @param p1Root 指向根结点
 */
void DrawInConsole(BalancedBinaryTreeNode *p1Root) {
  printf("DrawInConsole: \r\n");

  // 广度优先遍历的队列结构
  BalancedBinaryTreeNode *arr1Queue[TREE_NODE_NUM_MAX];
  int queueHead = 0, queueTail = 0;
  int tierNum = 1, tierTail = 0;
  BalancedBinaryTreeNode *t1Node;

  // 横坐标数据，[0,1=自己在的那个区间的起始坐标和结束坐标，2=父结点的横坐标]
  int arr2XCoordinate[TREE_NODE_NUM_MAX][3];
  // 临时，用于计算横坐标
  int t1MinX = 0;
  // 屏幕数据，[0=自己的结点值，1=自己的纵坐标，2=自己的横坐标，3=父结点的横坐标]
  int arr2PrintData[TREE_NODE_NUM_MAX][4];
  int arr2PrintDataLen = 0;
  // 屏幕缓冲区
  int arr2PrintBuffer[TIER_NUM_MAX * 4][TIER_NODE_NUM_MAX];

  // 初始化
  memset(arr1Queue, 0, sizeof(BalancedBinaryTreeNode *) * TREE_NODE_NUM_MAX);
  memset(arr2XCoordinate, 0, sizeof(int) * TREE_NODE_NUM_MAX * 3);
  memset(arr2PrintData, 0, sizeof(int) * TREE_NODE_NUM_MAX * 4);
  memset(arr2PrintBuffer, 0, sizeof(int) * TIER_NUM_MAX * 4 * TIER_NODE_NUM_MAX);

  arr1Queue[queueTail] = p1Root;
  arr2XCoordinate[queueTail][0] = 0;
  arr2XCoordinate[queueTail][1] = (1 << GetDepth(p1Root)) - 1;
  queueTail++;

  while (queueHead < queueTail) {
    tierTail = queueTail;
    while (queueHead < tierTail) {
      t1Node = arr1Queue[queueHead];
      arr2PrintData[arr2PrintDataLen][0] = t1Node->num;

      // 当前层次遍历到的层数，就是纵坐标
      arr2PrintData[arr2PrintDataLen][1] = tierNum;

      // 计算自己的横坐标（自己在的那个区间的中点坐标）
      t1MinX = (arr2XCoordinate[queueHead][0] + arr2XCoordinate[queueHead][1]) / 2;
      arr2PrintData[arr2PrintDataLen][2] = t1MinX;

      arr2PrintData[arr2PrintDataLen][3] = arr2XCoordinate[queueHead][2];

      if (t1Node->p1Left != NULL) {
        arr1Queue[queueTail] = t1Node->p1Left;
        arr2XCoordinate[queueTail][0] = arr2XCoordinate[queueHead][0];
        arr2XCoordinate[queueTail][1] = t1MinX - 1;
        arr2XCoordinate[queueTail][2] = t1MinX;
        queueTail++;
      }

      if (t1Node->p1Right != NULL) {
        arr1Queue[queueTail] = t1Node->p1Right;
        arr2XCoordinate[queueTail][0] = t1MinX + 1;
        arr2XCoordinate[queueTail][1] = arr2XCoordinate[queueHead][1];
        arr2XCoordinate[queueTail][2] = t1MinX;
        queueTail++;
      }

      queueHead++;
      arr2PrintDataLen++;
    }
    tierNum++;
  }

  // 用屏幕数据计算屏幕缓冲区的数据
  // 每层结点需要 4 行屏幕缓冲区。第 1 行放置结点值；第 2-4 行放置结点之间的连线。
  for (int i = 0; i < arr2PrintDataLen; i++) {
    // 计算结点值的坐标
    arr2PrintBuffer[(arr2PrintData[i][1] - 1) * 4][arr2PrintData[i][2]] = arr2PrintData[i][0];
    // 计算和父结点之间的连线怎么画
    if (arr2PrintData[i][2] < arr2PrintData[i][3]) {
      // 结点横坐标在父结点横坐标左边
      // 父结点的正下方，放一个分叉
      arr2PrintBuffer[(arr2PrintData[i][1] - 2) * 4 + 1][arr2PrintData[i][3]] = -1;
      // 从自己的正上方向右一个位置开始，直到父结点的正下方向左一个位置，填充连线
      for (int index = arr2PrintData[i][2] + 1; index < arr2PrintData[i][3]; index++) {
        arr2PrintBuffer[(arr2PrintData[i][1] - 2) * 4 + 2][index] = -2;
      }
      // 自己的正上方，放一个分叉
      arr2PrintBuffer[(arr2PrintData[i][1] - 2) * 4 + 3][arr2PrintData[i][2]] = -3;
    }
    if (arr2PrintData[i][2] > arr2PrintData[i][3]) {
      // 结点横坐标在父结点横坐标右边
      // 把上面的逻辑反过来画就行
      arr2PrintBuffer[(arr2PrintData[i][1] - 2) * 4 + 1][arr2PrintData[i][3]] = -1;
      for (int index = arr2PrintData[i][2] - 1; index > arr2PrintData[i][3]; index--) {
        arr2PrintBuffer[(arr2PrintData[i][1] - 2) * 4 + 2][index] = -2;
      }
      arr2PrintBuffer[(arr2PrintData[i][1] - 2) * 4 + 3][arr2PrintData[i][2]] = -4;
    }
  }

  // 在控制台输出屏幕缓冲区中的内容
  // 屏幕缓冲区中有效的数据只有 (tierNum - 1) * 4 - 3 行,
  for (int i = 0; i < (tierNum - 1) * 4 - 3; i++) {
    for (int j = 0; j < TIER_NODE_NUM_MAX; j++) {
      if (arr2PrintBuffer[i][j] == 0) {
        printf("   ");
      } else if (arr2PrintBuffer[i][j] == -1) {
        printf("/ \\");
      } else if (arr2PrintBuffer[i][j] == -2) {
        printf("---");
      } else if (arr2PrintBuffer[i][j] == -3) {
        printf("  /");
      } else if (arr2PrintBuffer[i][j] == -4) {
        printf("\\  ");
      } else {
        printf("%03d", arr2PrintBuffer[i][j]);
      }
    }
    printf("\r\n");
  }
}

/**
 * 计算与平衡值相关的结点深度
 * @param p1Node
 * @return
 */
int getDepthForBalance(BalancedBinaryTreeNode *p1Node) {
  int depthL = 0;
  int depthR = 0;

  if (p1Node->p1Left != NULL) {
    depthL = p1Node->p1Left->depth;
  }
  if (p1Node->p1Right != NULL) {
    depthR = p1Node->p1Right->depth;
  }

  if (depthL >= depthR) {
    return depthL + 1;
  } else {
    return depthR + 1;
  }
}

/**
 * 计算结点平衡值
 * @param p1Node
 * @return
 */
int getBalance(BalancedBinaryTreeNode *p1Node) {
  int depthL = 0, depthR = 0;

  if (p1Node->p1Left != NULL) {
    depthL = p1Node->p1Left->depth;
  }
  if (p1Node->p1Right != NULL) {
    depthR = p1Node->p1Right->depth;
  }

  return depthL - depthR;
}

/**
 * 左旋
 * @param p1Node 指向要旋转的那个结点
 * @param p2Root 指向，指向根结点的指针，的指针
 */
void leftRotate(BalancedBinaryTreeNode *p1Node, BalancedBinaryTreeNode **p2Root) {
  printf("leftRotate: %d\r\n", p1Node->num);

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
  p1Node->depth = getDepthForBalance(p1Node);
  p1Right->depth = getDepthForBalance(p1Right);

  DrawInConsole(*p2Root);
}

/**
 * 右旋
 * @param p1Node 指向要旋转的那个结点
 * @param p2Root 指向，指向根结点的指针，的指针
 */
void rightRotate(BalancedBinaryTreeNode *p1Node, BalancedBinaryTreeNode **p2Root) {
  printf("rightRotate: %d\r\n", p1Node->num);

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
  p1Node->depth = getDepthForBalance(p1Node);
  p1Left->depth = getDepthForBalance(p1Left);

  DrawInConsole(*p2Root);
}

/**
 * 中序遍历，左根右
 * @param p1Root 指向根结点
 */
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

/**
 * 计算二叉树深度
 * @param p1Node 指向根结点
 * @return
 */
int GetDepth(BalancedBinaryTreeNode *p1Node) {
  int leftDepth, rightDepth;

  if (p1Node == NULL) {
    return 0;
  }

  leftDepth = GetDepth(p1Node->p1Left);
  rightDepth = GetDepth(p1Node->p1Right);

  if (leftDepth >= rightDepth) {
    return leftDepth + 1;
  } else {
    return rightDepth + 1;
  }
}
