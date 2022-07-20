#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

// ## 二叉树 ##

// 用极值标记无效的结点
#define INT_MIN (1<<31)
#define INT_MAX (-((1<<31)+1))

#define TIER_NUM_MAX 8
#define TIER_NODE_NUM_MAX (1<<(TIER_NUM_MAX-1))
#define TREE_NODE_NUM_MAX ((1<<TIER_NUM_MAX)-1)

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
// 深度优先遍历
// BinaryTreeNode *，指向根结点
extern void DepthFirstSearch(BinaryTreeNode *);
void setColor(int m);
void BuildBinaryTreeFromArray(BinaryTreeNode **p2Node, int *p1arr1Num, int arr1NumLen, int index) {
  // 用数组保存的二叉树结构。
  // 先用无效结点把二叉树补成完全二叉树。深度为 n 的二叉树需要的数组大小为 2^(n)-1。
  // 从数组下标为 1 的位置开始存放二叉树的结点（下标为 0 的位置可以放二叉树的总结点数），顺序是从上到下从左到右。
  // 这样，下标为 n 的结点的，左子树的根结点下标为 2*n，右子树的根结点下标为 2*n+1，父结点的下标是 i/2 向下取整。
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

    // 用数组保存二叉树结构时，二叉树结点与子结点的关系可以通过数组下标体现
    // 这里把这次构造的结点的左右结点传递下去，用递归的方式分别构造左右子树
    BuildBinaryTreeFromArray(&((*p2Node)->p1Left), p1arr1Num, arr1NumLen, index * 2);
    BuildBinaryTreeFromArray(&((*p2Node)->p1Right), p1arr1Num, arr1NumLen, index * 2 + 1);
  }
}

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

int GetDepth(BinaryTreeNode *p1Node) {
  int leftDepth = 0, rightDepth = 0;

  if (p1Node == NULL) {
    return 0;
  }

  leftDepth = GetDepth(p1Node->p1Left);
  rightDepth = GetDepth(p1Node->p1Right);
  return (int)fmax(leftDepth, rightDepth) + 1;
}

void BreadthFirstSearch(BinaryTreeNode *p1Root) {
  printf("BreadthFirstSearch: ");

  // 广度优先遍历需要借助队列结构
  // 队列
  BinaryTreeNode *arr1Queue[TREE_NODE_NUM_MAX];
  memset(arr1Queue,0,sizeof(BinaryTreeNode*)*TREE_NODE_NUM_MAX);
  // 队列头，队列尾
  int queueHead = 0, queueTail = 0;
  // 当前遍历的层；当前层的最后一个结点在队列中的下标
  int tierNum = 1, tierTail = 0;
  BinaryTreeNode *t1Node;

  arr1Queue[queueTail] = p1Root;
  queueTail++;

  // 持续遍历，直到队列为空
  while (queueHead < queueTail) {
    // 遍历当前遍历的层中的结点
    tierTail = queueTail;
    while (queueHead < tierTail) {
      t1Node = arr1Queue[queueHead];
      queueHead++;
      if (NULL==t1Node){
        continue;
      }
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
    }
    // 层数 + 1
    tierNum++;
  }

  printf("\r\n");
}

void DepthFirstSearch(BinaryTreeNode *p1Root) {
  printf("DepthFirstSearch: ");

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

  printf("\r\n");
}

void DrawInConsole(BinaryTreeNode *p1Root){
  int depth = GetDepth(p1Root);
  int abscissa = (1<<depth)-1;

  BinaryTreeNode *arr1Queue[TREE_NODE_NUM_MAX];
  memset(arr1Queue,0,sizeof(BinaryTreeNode*)*TREE_NODE_NUM_MAX);

  int arr1locate[TREE_NODE_NUM_MAX][3];
  memset(arr1locate,0,sizeof(int)*TREE_NODE_NUM_MAX*3);
  int arr1res[TREE_NODE_NUM_MAX][4];
  memset(arr1res,0,sizeof(int)*TREE_NODE_NUM_MAX*4);

  int arr1resLen = 0;

  int queueHead = 0, queueTail = 0;
  int tierNum = 1, tierTail = 0;
  BinaryTreeNode *t1Node;

  arr1Queue[queueTail] = p1Root;
  arr1locate[queueTail][0] = 0;
  arr1locate[queueTail][1] = abscissa;
  queueTail++;

  while (queueHead < queueTail) {
    // 遍历当前遍历的层中的结点
    tierTail = queueTail;
    while (queueHead < tierTail) {
      int locate = (arr1locate[queueHead][0]+arr1locate[queueHead][1])/2;
      t1Node = arr1Queue[queueHead];

      arr1res[arr1resLen][0]=t1Node->num;
      arr1res[arr1resLen][1]=tierNum;
      arr1res[arr1resLen][2]=locate;
      arr1res[arr1resLen][3]=arr1locate[queueHead][2];

      if (NULL==t1Node){
        queueHead++;
        continue;
      }
      printf("%d-%d,", tierNum, t1Node->num);
      if (t1Node->p1Left != NULL) {
        // 左结点先入队，先遍历
        arr1Queue[queueTail] = t1Node->p1Left;
        arr1locate[queueTail][0] = arr1locate[queueHead][0];
        arr1locate[queueTail][1] = locate-1;
        arr1locate[queueTail][2] = locate;
        queueTail++;
      }
      if (t1Node->p1Right != NULL) {
        // 右结点后入队，后遍历
        arr1Queue[queueTail] = t1Node->p1Right;
        arr1locate[queueTail][0] = locate+1;
        arr1locate[queueTail][1] = arr1locate[queueHead][1];
        arr1locate[queueTail][2] = locate;
        queueTail++;
      }
      queueHead++;
      arr1resLen++;
    }
    // 层数 + 1
    tierNum++;
  }
  int print[TIER_NUM_MAX][TIER_NODE_NUM_MAX];
  memset(print,0,sizeof(int)*TIER_NUM_MAX*TIER_NODE_NUM_MAX);
  for (int i=0;i<arr1resLen;i++){
    print[arr1res[i][1]-1][arr1res[i][2]]=arr1res[i][0];
    if(arr1res[i][2]<arr1res[i][3]){
      for(int a=arr1res[i][2];a<arr1res[i][3];a++){
        print[arr1res[i][1]-2][a]=-1;
      }
    }
    if(arr1res[i][2]>arr1res[i][3]){
      for(int a=arr1res[i][2];a>arr1res[i][3];a--){
        print[arr1res[i][1]-2][a]=-1;
      }
    }
  }

  printf("\r\n");
  for (int i=0;i<TIER_NUM_MAX;i++){
    for (int j=0;j<TIER_NODE_NUM_MAX;j++){
      if (print[i][j]==0){
        printf("     ");
      }else if (print[i][j]==-1){
        printf(" --- ");
      }else {
        setColor(4);
        printf("[%3d]", print[i][j]);
      }
    }
    printf("\r\n");
  }
}

void setColor(int m){
  HANDLE consolehend;
  consolehend= GetStdHandle(STD_OUTPUT_HANDLE);
  SetConsoleTextAttribute(consolehend,m);
}
