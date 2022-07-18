#include <stdio.h>

#include "huffman_tree.c"

// 单元测试
void HuffmanTreeUnitTesting();

int main() {
  HuffmanTreeUnitTesting();
  return 0;
}

void HuffmanTreeUnitTesting() {
  // 待处理字符串
  char str[] = "hello, world";
  // 字符数组，初始化全为 '\0'，下标和 ASICC 码一一对应
  char arr1Char[MAX_CHAR_NUM];
  // 字符权重数组，初始化全为 0，下标和 ASICC 码一一对应
  int arr1Weight[MAX_CHAR_NUM];

  // 指向哈夫曼编树根结点
  HuffmanTreeNode *p1Root = NULL;
  // 哈夫曼编码表，指针数组，每个指针存储一个字符的编码
  char *arr1p1Code[MAX_CHAR_NUM];
  // 临时，用于编码的字符串
  char arr1t1Coding[MAX_ENCODE_LEN];
  // 编码后的字符串
  char strEncode[MAX_CHAR_NUM * MAX_ENCODE_LEN + 1];
  // 解码后的字符串
  char strDecode[MAX_CHAR_NUM * MAX_ENCODE_LEN + 1];

  memset(arr1Char, 0, sizeof(char) * MAX_CHAR_NUM);
  memset(arr1Weight, 0, sizeof(int) * MAX_CHAR_NUM);
  memset(arr1p1Code, 0, sizeof(char *) * MAX_CHAR_NUM);
  memset(arr1t1Coding, 0, sizeof(char) * MAX_ENCODE_LEN);
  memset(strEncode, 0, sizeof(char) * (MAX_CHAR_NUM * MAX_ENCODE_LEN + 1));

  // 统计字符权重
  for (int i = 0; str[i] != '\0'; i++) {
    arr1Char[(int)str[i]] = str[i];
    arr1Weight[(int)str[i]]++;
  }

  BuildHuffmanTree(&p1Root, arr1Char, arr1Weight);
  MakeHuffmanCode(p1Root, arr1p1Code, arr1t1Coding, 0);

  for (int i = 0; i < MAX_CHAR_NUM; i++) {
    if (NULL == arr1p1Code[i]) {
      continue;
    }
    printf("%c, %s\r\n", (char)i, arr1p1Code[i]);
  }

  HuffmanEncode(str, arr1p1Code, strEncode);
  printf("encode: %s\r\n", strEncode);

  HuffmanDecode(p1Root, strEncode, strDecode);
  printf("decode: %s\r\n", strDecode);
}