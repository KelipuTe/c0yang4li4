#include <stdlib.h>
#include <string.h>

// ## 哈夫曼树 ##

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

// 字符表最大数量
// ASICC 码一共 128 个
#define MAX_CHAR_NUM 128
// 编码的最大长度
#define MAX_ENCODE_LEN 32

typedef struct HuffmanTreeNode {
  // 结点存储的字符
  // 结点有两种，一种是单纯的叶子结点，用于存储字符；另一种是合并出来的权重结点，权重结点存储 '\0' 用于区分。
  char character;
  // 结点权重
  int weight;
  // 指向左子树的根结点
  struct HuffmanTreeNode *p1Left;
  // 指向右子树的根结点
  struct HuffmanTreeNode *p1Right;
} HuffmanTreeNode;

extern void BuildHuffmanTree(HuffmanTreeNode **, char *, int *);
extern void DrawInConsole(HuffmanTreeNode *);
extern void MakeHuffmanCode(HuffmanTreeNode *, char *[MAX_CHAR_NUM], char *, int);
extern void HuffmanEncode(char *, char *[MAX_CHAR_NUM], char *);
extern void HuffmanDecode(HuffmanTreeNode *, char *, char *);

/**
 * 构造哈夫曼树
 * @param p2Root 指向，指向根结点指针，的指针
 * @param arr1Char 字符数组
 * @param arr1Weight 字符权重数组
 */
void BuildHuffmanTree(HuffmanTreeNode **p2Root, char *arr1Char, int *arr1Weight) {
  // 所有指向字符结点的指针的数组
  HuffmanTreeNode *arr1p1Node[MAX_CHAR_NUM];
  // 所有指向字符结点的指针的数组长度
  int arr1p1NodeLen = 0;

  // 临时，数组下标
  int t1Index1, t1Index2;
  // 临时，指向字符结点的指针
  HuffmanTreeNode *t1Node;

  memset(arr1p1Node, 0, sizeof(HuffmanTreeNode *) * MAX_CHAR_NUM);

  for (int i = 0; i < MAX_CHAR_NUM; i++) {
    if ('\0' == arr1Char[i]) {
      continue;
    }
    arr1p1Node[arr1p1NodeLen] = (HuffmanTreeNode *)malloc(sizeof(HuffmanTreeNode));
    arr1p1Node[arr1p1NodeLen]->character = arr1Char[i];
    arr1p1Node[arr1p1NodeLen]->weight = arr1Weight[i];
    arr1p1Node[arr1p1NodeLen]->p1Left = NULL;
    arr1p1Node[arr1p1NodeLen]->p1Right = NULL;
    arr1p1NodeLen++;
  }

  while (1) {
    // 重置数组下标
    t1Index1 = -1;
    t1Index2 = -1;
    // 找到权重最小的两个结点
    for (int i = 0; i < arr1p1NodeLen; i++) {
      if (NULL == arr1p1Node[i]) {
        continue;
      }
      if (-1 == t1Index1) {
        t1Index1 = i;
      } else if (-1 == t1Index2) {
        t1Index2 = i;
      } else {
        if (arr1p1Node[i]->weight < arr1p1Node[t1Index1]->weight && arr1p1Node[i]->weight < arr1p1Node[t1Index2]->weight) {
          if (arr1p1Node[t1Index1]->weight > arr1p1Node[t1Index2]->weight) {
            t1Index1 = i;
          } else {
            t1Index2 = i;
          }
          continue;
        }
        if (arr1p1Node[i]->weight < arr1p1Node[t1Index1]->weight) {
          t1Index1 = i;
          continue;
        }
        if (arr1p1Node[i]->weight < arr1p1Node[t1Index2]->weight) {
          t1Index2 = i;
          continue;
        }
      }
    }
    if (-1 != t1Index1 && -1 != t1Index2) {
      // 如果能找到两个结点，就以这两个结点作为子结点构造一个父结点
      t1Node = (HuffmanTreeNode *)malloc(sizeof(HuffmanTreeNode));
      t1Node->character = '\0';
      t1Node->weight = arr1p1Node[t1Index1]->weight + arr1p1Node[t1Index2]->weight;
      t1Node->p1Left = arr1p1Node[t1Index1];
      t1Node->p1Right = arr1p1Node[t1Index2];
      // 把原来的两个结点从指针数组中移除，把新构造的结点放入指针数组
      arr1p1Node[t1Index1] = t1Node;
      arr1p1Node[t1Index2] = NULL;
    } else {
      // 指针数组中只剩一个结点，那么哈夫曼树就已经构造完成了
      if (-1 != t1Index1) {
        *p2Root = arr1p1Node[t1Index1];
        break;
      }
      if (-1 != t1Index2) {
        *p2Root = arr1p1Node[t1Index2];
        break;
      }
    }
  }
}

/**
 * 计算二叉树深度
 * @param p1Node 指向根结点
 * @return
 */
int GetDepth(HuffmanTreeNode *p1Node) {
  int leftDepth, rightDepth;

  if (NULL == p1Node) {
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
 * 在控制台输出二叉树，需要借助层次遍历的逻辑
 * @param p1Root 指向根结点
 */
void DrawInConsole(HuffmanTreeNode *p1Root) {
  printf("DrawInConsole: \r\n");

  // 广度优先遍历的队列结构
  HuffmanTreeNode *arr1Queue[TREE_NODE_NUM_MAX];
  int queueHead = 0, queueTail = 0;
  int tierNum = 1, tierTail = 0;
  HuffmanTreeNode *t1Node;

  // 横坐标数据，[0,1=自己在的那个区间的起始坐标和结束坐标，2=父结点的横坐标]
  int arr2XCoordinate[TREE_NODE_NUM_MAX][3];
  // 临时，用于计算横坐标
  int t1MinX = 0;
  // 屏幕数据，[0=自己的结点值，1=自己的纵坐标，2=自己的横坐标，3=父结点的横坐标，4=结点的字符]
  int arr2PrintData[TREE_NODE_NUM_MAX][5];
  int arr2PrintDataLen = 0;
  // 屏幕缓冲区，坐标上需要存储两个数据，0=结点数值；1=结点字符
  int arr2PrintBuffer[TIER_NUM_MAX * 4][TIER_NODE_NUM_MAX][2];

  // 初始化
  memset(arr1Queue, 0, sizeof(HuffmanTreeNode *) * TREE_NODE_NUM_MAX);
  memset(arr2XCoordinate, 0, sizeof(int) * TREE_NODE_NUM_MAX * 3);
  memset(arr2PrintData, 0, sizeof(int) * TREE_NODE_NUM_MAX * 4);
  memset(arr2PrintBuffer, 0, sizeof(int) * TIER_NUM_MAX * 4 * TIER_NODE_NUM_MAX * 2);

  arr1Queue[queueTail] = p1Root;
  arr2XCoordinate[queueTail][0] = 0;
  arr2XCoordinate[queueTail][1] = (1 << GetDepth(p1Root)) - 1;
  queueTail++;

  while (queueHead < queueTail) {
    tierTail = queueTail;
    while (queueHead < tierTail) {
      t1Node = arr1Queue[queueHead];
      arr2PrintData[arr2PrintDataLen][0] = (int)t1Node->weight;

      // 当前层次遍历到的层数，就是纵坐标
      arr2PrintData[arr2PrintDataLen][1] = tierNum;

      // 计算自己的横坐标（自己在的那个区间的中点坐标）
      t1MinX = (arr2XCoordinate[queueHead][0] + arr2XCoordinate[queueHead][1]) / 2;
      arr2PrintData[arr2PrintDataLen][2] = t1MinX;

      arr2PrintData[arr2PrintDataLen][3] = arr2XCoordinate[queueHead][2];

      arr2PrintData[arr2PrintDataLen][4] = (int)t1Node->character;

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
    arr2PrintBuffer[(arr2PrintData[i][1] - 1) * 4][arr2PrintData[i][2]][0] = arr2PrintData[i][0];
    arr2PrintBuffer[(arr2PrintData[i][1] - 1) * 4][arr2PrintData[i][2]][1] = arr2PrintData[i][4];
    // 计算和父结点之间的连线怎么画
    if (arr2PrintData[i][2] < arr2PrintData[i][3]) {
      // 结点横坐标在父结点横坐标左边
      // 父结点的正下方，放一个分叉
      arr2PrintBuffer[(arr2PrintData[i][1] - 2) * 4 + 1][arr2PrintData[i][3]][0] = -1;
      // 从自己的正上方向右一个位置开始，直到父结点的正下方向左一个位置，填充连线
      for (int index = arr2PrintData[i][2] + 1; index < arr2PrintData[i][3]; index++) {
        arr2PrintBuffer[(arr2PrintData[i][1] - 2) * 4 + 2][index][0] = -2;
      }
      // 自己的正上方，放一个分叉
      arr2PrintBuffer[(arr2PrintData[i][1] - 2) * 4 + 3][arr2PrintData[i][2]][0] = -3;
    }
    if (arr2PrintData[i][2] > arr2PrintData[i][3]) {
      // 结点横坐标在父结点横坐标右边
      // 把上面的逻辑反过来画就行
      arr2PrintBuffer[(arr2PrintData[i][1] - 2) * 4 + 1][arr2PrintData[i][3]][0] = -1;
      for (int index = arr2PrintData[i][2] - 1; index > arr2PrintData[i][3]; index--) {
        arr2PrintBuffer[(arr2PrintData[i][1] - 2) * 4 + 2][index][0] = -2;
      }
      arr2PrintBuffer[(arr2PrintData[i][1] - 2) * 4 + 3][arr2PrintData[i][2]][0] = -4;
    }
  }

  // 在控制台输出屏幕缓冲区中的内容
  // 屏幕缓冲区中有效的数据只有 (tierNum - 1) * 4 - 3 行,
  for (int i = 0; i < (tierNum - 1) * 4 - 3; i++) {
    for (int j = 0; j < TIER_NODE_NUM_MAX; j++) {
      if (arr2PrintBuffer[i][j][0] == 0) {
        printf("    ");
      } else if (arr2PrintBuffer[i][j][0] == -1) {
        printf("/  \\");
      } else if (arr2PrintBuffer[i][j][0] == -2) {
        printf("----");
      } else if (arr2PrintBuffer[i][j][0] == -3) {
        printf("  / ");
      } else if (arr2PrintBuffer[i][j][0] == -4) {
        printf(" \\  ");
      } else {
        printf("%03d", arr2PrintBuffer[i][j][0]);
        if (arr2PrintBuffer[i][j][1] != 0) {
          printf("%c", arr2PrintBuffer[i][j][1]);
        } else {
          printf("_");
        }
      }
    }
    printf("\r\n");
  }
}

/**
 * 构造哈夫曼编码
 * @param p1Node
 * @param arr1p1Code
 * @param arr1t1Coding
 * @param codeLen
 */
void MakeHuffmanCode(HuffmanTreeNode *p1Node, char *arr1p1Code[MAX_CHAR_NUM], char *arr1t1Coding, int codeLen) {
  if (NULL == p1Node) {
    return;
  }

  if ('\0' == p1Node->character) {
    // 如果是合并出来的结点，就继续递归
    if (p1Node->p1Left != NULL) {
      arr1t1Coding[codeLen] = '0';
      codeLen++;
      MakeHuffmanCode(p1Node->p1Left, arr1p1Code, arr1t1Coding, codeLen);
      codeLen--;
    }
    if (p1Node->p1Right != NULL) {
      arr1t1Coding[codeLen] = '1';
      codeLen++;
      MakeHuffmanCode(p1Node->p1Right, arr1p1Code, arr1t1Coding, codeLen);
      codeLen--;
    }
  } else {
    // 如果是字符结点，那么这个字符就完成了编码
    arr1p1Code[(int)p1Node->character] = malloc(sizeof(char) * (codeLen + 1));
    for (int i = 0; i < codeLen; i++) {
      arr1p1Code[(int)p1Node->character][i] = arr1t1Coding[i];
    }
    arr1p1Code[(int)p1Node->character][codeLen] = '\0';
  }
}

/**
 * 把字符串进行哈夫曼编码
 * @param str
 * @param arr1p1Code
 * @param strEncode
 */
void HuffmanEncode(char *str, char *arr1p1Code[MAX_CHAR_NUM], char *strEncode) {
  int i = 0;
  int strEncodeLen = 0;
  while (str[i] != '\0') {
    char *charEncode = arr1p1Code[(int)str[i]];
    for (int j = 0; charEncode[j] != '\0'; j++) {
      strEncode[strEncodeLen] = charEncode[j];
      strEncodeLen++;
    }
    i++;
  }
  strEncode[strEncodeLen] = '\0';
}

/**
 * 把哈夫曼编码的字符串进行解码
 * @param p1Root
 * @param strEncode
 * @param strDecode
 */
void HuffmanDecode(HuffmanTreeNode *p1Root, char *strEncode, char *strDecode) {
  HuffmanTreeNode *p1Node = p1Root;

  int strDecodeLen = 0;
  for (int i = 0; strEncode[i] != '\0'; i++) {
    if ('0' == strEncode[i]) {
      p1Node = p1Node->p1Left;
    } else if ('1' == strEncode[i]) {
      p1Node = p1Node->p1Right;
    } else {
      // 解析失败
      return;
    }
    // 看看有没有命中字符结点
    if (p1Node->character != '\0') {
      strDecode[strDecodeLen] = p1Node->character;
      strDecodeLen++;
      p1Node = p1Root;
    }
  }
}
