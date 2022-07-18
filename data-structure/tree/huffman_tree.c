#include <stdlib.h>
#include <string.h>

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

// 构造哈夫曼树
// HuffmanTreeNode **，指向，指向根结点指针，的指针
// char *，字符数组
// int *，字符权重数组
extern void BuildHuffmanTree(HuffmanTreeNode **, char *, int *);
// 构造哈夫曼编码
// char *[MAX_CHAR_NUM]，
extern void MakeHuffmanCode(HuffmanTreeNode *, char *[MAX_CHAR_NUM], char *, int);
// 把字符串进行哈夫曼编码
extern void HuffmanEncode(char *, char *[MAX_CHAR_NUM], char *);
// 把哈夫曼编码的字符串进行解码
extern void HuffmanDecode(HuffmanTreeNode *, char *, char *);

extern void BuildHuffmanTree(HuffmanTreeNode **p2Root, char *arr1Char, int *arr1Weight) {
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
