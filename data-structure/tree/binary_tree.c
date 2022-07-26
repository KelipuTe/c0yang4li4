#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ## 二叉树 ##

// 用极值标记无效的结点
#define INT_MIN (1 << 31)
#define INT_MAX (-((1 << 31) + 1))

// 二叉树最大层数
#define TIER_NUM_MAX 8
// 最下层最大结点数
#define TIER_NODE_NUM_MAX (1 << (TIER_NUM_MAX - 1))
// 二叉树最大结点数
#define TREE_NODE_NUM_MAX ((1 << TIER_NUM_MAX) - 1)

// 二叉树结点
typedef struct BinaryTreeNode {
  // 结点值
  int num;
  // 指向左子树的根结点
  struct BinaryTreeNode *p1Left;
  // 指向右子树的根结点
  struct BinaryTreeNode *p1Right;
} BinaryTreeNode;

extern void PrintDefine();
extern void BuildBinaryTreeFromArray(BinaryTreeNode **, int *, int, int);
extern void DrawInConsole(BinaryTreeNode *);
extern void PreorderTraversal(BinaryTreeNode *);
void doPreorderTraversal(BinaryTreeNode *);
extern void InorderTraversal(BinaryTreeNode *);
void doInorderTraversal(BinaryTreeNode *);
extern void SubsequentTraversal(BinaryTreeNode *);
void doSubsequentTraversal(BinaryTreeNode *);
extern int GetDepth(BinaryTreeNode *);
extern void BreadthFirstSearch(BinaryTreeNode *);
extern void DepthFirstSearch(BinaryTreeNode *);

/**
 * 输出 #define 定义的数据
 */
void PrintDefine() {
  printf("INT_MIN = %d\r\n", INT_MIN);
  printf("INT_MAX = +%d\r\n", INT_MAX);
  printf("TIER_NUM_MAX      = %d\r\n", TIER_NUM_MAX);
  printf("TIER_NODE_NUM_MAX = %d\r\n", TIER_NODE_NUM_MAX);
  printf("TREE_NODE_NUM_MAX = %d\r\n", TREE_NODE_NUM_MAX);
}

/**
 * 从数组构造二叉树
 * @param p2Node 指向二叉树的，指向左子树的根结点的指针或者指向右子树的根结点的指针，的指针
 * @param p1arr1Num 保存二叉树的数组
 * @param arr1NumLen 保存二叉树的数组的长度
 * @param index 本次构造的结点在保存二叉树的数组中的下标
 */
void BuildBinaryTreeFromArray(BinaryTreeNode **p2Node, int *p1arr1Num, int arr1NumLen, int index) {
  // 用数组保存的二叉树时，先用无效结点把二叉树补成完全二叉树。深度为 n 的二叉树需要的数组大小为 2^(n)-1。
  // 从数组下标为 1 的位置开始存放二叉树的结点（下标为 0 的位置可以放二叉树的总结点数），顺序是从上到下从左到右。
  // 这样，二叉树结点与子结点的关系可以通过数组下标体现。
  // 下标为 n 的结点的，左子树的根结点下标为 2*n，右子树的根结点下标为 2*n+1，父结点的下标是 n/2 向下取整。
  if (index >= arr1NumLen) {
    return;
  }
  if (p1arr1Num[index] == INT_MIN) {
    // 如果数组中这个位置是无效值，则不构造这个结点
    *p2Node = NULL;
  } else {
    // 如果数组中这个位置是有效值，则构造这个结点
    *p2Node = (BinaryTreeNode *)malloc(sizeof(BinaryTreeNode));
    (*p2Node)->num = p1arr1Num[index];
    (*p2Node)->p1Left = NULL;
    (*p2Node)->p1Right = NULL;

    // 这里把这次构造的结点的左右结点传递下去，用递归的方式分别构造左右子树
    BuildBinaryTreeFromArray(&((*p2Node)->p1Left), p1arr1Num, arr1NumLen, index * 2);
    BuildBinaryTreeFromArray(&((*p2Node)->p1Right), p1arr1Num, arr1NumLen, index * 2 + 1);
  }
}

/**
 * 在控制台输出二叉树，需要借助层次遍历的逻辑
 * @param p1Root 指向根结点
 */
void DrawInConsole(BinaryTreeNode *p1Root) {
  // 在控制台输出二叉树的思路是：
  // 先把二叉树保留左右子树的相对位置，向下拍扁，借此计算每个结点在屏幕上的横坐标。
  // 然后，再借助层次遍历的逻辑，计算每个结点在屏幕上的纵坐标。

  // 比如，如下一棵二叉树：
  //                   001
  //               /         \
  //             002         003
  //            /   \       /   \
  //          004   005   006   007
  // 向下拍扁之后的样子是：004，002，005，001，006，003，007

  // 首先可以通过计算二叉树的深度，得到拍扁时需要多大的存储空间（3 层的二叉树需要 7（2^3-1）个位置）。
  // 借助层次遍历的逻辑，依次计算每个结点的横纵坐标。每个结点的位置都在对应区间的中间，算完上一层，再算下一层。
  // 001 在下标 3 的位置上，在整个区间的中间（下标 0 到 6 的中间）。第一层算完了，算第二层。
  // 002 在下标 1 的位置上，在 001 结点左边的整个区间的中间（下标 0 到 2 的中间）；
  // 002 在下标 5 的位置上，在 001 结点右边的整个区间的中间（下标 4 到 6 的中间）。第二层算完了，算第三层。

  printf("DrawInConsole: \r\n");

  // 广度优先遍历的队列结构
  BinaryTreeNode *arr1Queue[TREE_NODE_NUM_MAX];
  int queueHead = 0, queueTail = 0;
  int tierNum = 1, tierTail = 0;
  BinaryTreeNode *t1Node;

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
  memset(arr1Queue, 0, sizeof(BinaryTreeNode *) * TREE_NODE_NUM_MAX);
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
 * 前序遍历，根左右
 * @param p1Root 指向根结点
 */
void PreorderTraversal(BinaryTreeNode *p1Root) {
  printf("PreorderTraversal: ");
  doPreorderTraversal(p1Root);
  printf("\r\n");
}

void doPreorderTraversal(BinaryTreeNode *p1Node) {
  if (p1Node == NULL) {
    return;
  }

  printf("%d,", p1Node->num);
  doPreorderTraversal(p1Node->p1Left);
  doPreorderTraversal(p1Node->p1Right);
}

/**
 * 中序遍历，左根右
 * @param p1Root 指向根结点
 */
void InorderTraversal(BinaryTreeNode *p1Root) {
  printf("InorderTraversal: ");
  doInorderTraversal(p1Root);
  printf("\r\n");
}

void doInorderTraversal(BinaryTreeNode *p1Node) {
  if (p1Node == NULL) {
    return;
  }

  doInorderTraversal(p1Node->p1Left);
  printf("%d,", p1Node->num);
  doInorderTraversal(p1Node->p1Right);
}

/**
 * 后序遍历，左右根
 * @param p1Root 指向根结点
 */
void SubsequentTraversal(BinaryTreeNode *p1Root) {
  printf("SubsequentTraversal: ");
  doSubsequentTraversal(p1Root);
  printf("\r\n");
}

void doSubsequentTraversal(BinaryTreeNode *p1Node) {
  if (p1Node == NULL) {
    return;
  }

  doSubsequentTraversal(p1Node->p1Left);
  doSubsequentTraversal(p1Node->p1Right);
  printf("%d,", p1Node->num);
}

/**
 * 计算二叉树深度
 * @param p1Node 指向根结点
 * @return
 */
int GetDepth(BinaryTreeNode *p1Node) {
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

/**
 * 广度优先遍历
 * @param p1Root 指向根结点
 */
void BreadthFirstSearch(BinaryTreeNode *p1Root) {
  printf("BreadthFirstSearch: ");

  // 队列（数组结构），广度优先遍历需要借助队列结构
  BinaryTreeNode *arr1Queue[TREE_NODE_NUM_MAX];
  // 队列头；队列尾
  int queueHead = 0, queueTail = 0;
  // 当前遍历的层，默认从 1 开始；当前层的最后一个结点在队列中的下标
  int tierNum = 1, tierTail = 0;
  // 临时，用于遍历
  BinaryTreeNode *t1Node;

  // 初始化
  memset(arr1Queue, 0, sizeof(BinaryTreeNode *) * TREE_NODE_NUM_MAX);

  // 放入根结点
  arr1Queue[queueTail] = p1Root;
  queueTail++;

  // 持续遍历，直到队列为空
  while (queueHead < queueTail) {
    // 持续遍历，当前遍历的层中的结点
    tierTail = queueTail;
    while (queueHead < tierTail) {
      t1Node = arr1Queue[queueHead];
      printf("%d-%d,", tierNum, t1Node->num);
      if (t1Node->p1Left != NULL) {
        // 左结点先入队，先遍历
        arr1Queue[queueTail] = t1Node->p1Left;
        queueTail++;
      }
      if (t1Node->p1Right != NULL) {
        // 右结点后入队，后遍历
        arr1Queue[queueTail] = t1Node->p1Right;
        queueTail++;
      }
      queueHead++;
    }
    // 层数 +1
    tierNum++;
  }
  printf("\r\n");
}

/**
 * 深度优先遍历
 * @param p1Root 指向根结点
 */
void DepthFirstSearch(BinaryTreeNode *p1Root) {
  printf("DepthFirstSearch: ");

  // 栈（数组结构），深度优先遍历需要借助栈存储结构
  BinaryTreeNode *arr1Stark[TREE_NODE_NUM_MAX];
  // 栈顶
  int startTop = 0;
  // 临时，用于遍历
  BinaryTreeNode *t1Node;

  // 初始化
  memset(arr1Stark, 0, sizeof(BinaryTreeNode *) * TREE_NODE_NUM_MAX);

  // 放入根结点
  arr1Stark[startTop] = p1Root;
  startTop++;

  // 持续遍历，直到栈为空
  while (startTop > 0) {
    --startTop;
    t1Node = arr1Stark[startTop];
    printf("%d,", t1Node->num);
    if (t1Node->p1Right != NULL) {
      // 右结点先入栈，后遍历
      arr1Stark[startTop] = t1Node->p1Right;
      startTop++;
    }
    if (t1Node->p1Left != NULL) {
      // 左结点后入栈，先遍历
      arr1Stark[startTop] = t1Node->p1Left;
      startTop++;
    }
  }
  printf("\r\n");
}
