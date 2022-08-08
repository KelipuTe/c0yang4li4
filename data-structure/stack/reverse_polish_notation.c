#include <stdio.h>
#include <string.h>

// ## 后缀表达式（逆波兰式、reverse polish notation、RPN） ##
// 使用后缀表达式处理带小括号的十进制正负两位整数的四则运算

// 表达式最大长度
#define NOTATION_MAX_LENGTH 256
// 操作数无效值
#define UNDEFINED_OPERATING_NUM (1 << 31)

// 四则运算
extern float fourFundamentalOperations(float a, float b, char t1operator);

int main() {
  // 中缀表达式（infix notation）
  char arr1IN[NOTATION_MAX_LENGTH] = "(-1-99)*(30+70)";

  // 操作数栈
  float arr1numStack[NOTATION_MAX_LENGTH];
  memset(arr1numStack, 0, sizeof(arr1numStack));
  int arr1numTop = -1;
  // 操作符栈
  char arr1operatorStack[NOTATION_MAX_LENGTH];
  memset(arr1operatorStack, 0, sizeof(arr1operatorStack));
  int arr1operatorTop = -1;

  // 临时，操作数
  float t1operatingNum = UNDEFINED_OPERATING_NUM;
  float t1a, t1b;
  // 临时，操作符
  char t1operator;

  // 开始处理
  for (int i = 0; i < NOTATION_MAX_LENGTH; i++) {
    if ('\0' == arr1IN[i]) {
      break;
    }
    if (arr1IN[i] >= '0' && arr1IN[i] <= '9') {
      // 处理操作数，注意两位数
      if (t1operatingNum != UNDEFINED_OPERATING_NUM) {
        t1operatingNum *= 10;
        t1operatingNum += (int)(arr1IN[i] - '0');
      } else {
        t1operatingNum = (int)(arr1IN[i] - '0');
      }
    } else {
      // 处理操作符
      if (t1operatingNum != UNDEFINED_OPERATING_NUM) {
        // 如果之前读到过有效的数字，就把数字入栈，然后重置为无效值
        arr1numTop++;
        arr1numStack[arr1numTop] = t1operatingNum;
        t1operatingNum = UNDEFINED_OPERATING_NUM;
      }

      switch (arr1IN[i]) {
        case '(':
          // 遇到右括号，直接操作符入栈
          arr1operatorTop++;
          arr1operatorStack[arr1operatorTop] = arr1IN[i];
          break;
        case ')':
          // 遇到右括号时，持续出栈操作符并进行计算，直到匹配到左括号
          while (1) {
            t1operator = arr1operatorStack[arr1operatorTop];
            arr1operatorTop--;
            if (t1operator == '(') {
              break;
            } else {
              t1a = arr1numStack[arr1numTop];
              arr1numTop--;
              t1b = arr1numStack[arr1numTop];
              arr1numTop--;
              arr1numTop++;
              arr1numStack[arr1numTop] = fourFundamentalOperations(t1b, t1a, t1operator);
            }
          }
          break;
        case '+':
        case '-':
          while (1) {
            t1operator = arr1operatorStack[arr1operatorTop];
            if ('+' == t1operator || '-' == t1operator || '*' == t1operator || '/' == t1operator) {
              // 如果加号和减号前面有其他操作符，则需要持续出栈操作符并进行计算
              t1operator = arr1operatorStack[arr1operatorTop];
              arr1operatorTop--;
              if (arr1numTop > -1) {
                t1a = arr1numStack[arr1numTop];
                arr1numTop--;
              } else {
                t1a = 0;
              }
              if (arr1numTop > -1) {
                t1b = arr1numStack[arr1numTop];
                arr1numTop--;
              } else {
                t1b = 0;
              }
              arr1numTop++;
              arr1numStack[arr1numTop] = fourFundamentalOperations(t1b, t1a, t1operator);
            } else {
              // 如果加号和减号前面没有其他操作符，直接操作符入栈
              arr1operatorTop++;
              arr1operatorStack[arr1operatorTop] = arr1IN[i];
              break;
            }
          }
          break;
        case '*':
        case '/':
          while (1) {
            // 如果乘号和除号前面有乘号或除号则需要出栈操作符并进行计算，加号或减号则不需要
            t1operator = arr1operatorStack[arr1operatorTop];
            if ('*' == t1operator || '/' == t1operator) {
              arr1operatorTop--;
              if (arr1numTop > -1) {
                t1a = arr1numStack[arr1numTop];
                arr1numTop--;
              } else {
                t1a = 0;
              }
              if (arr1numTop > -1) {
                t1b = arr1numStack[arr1numTop];
                arr1numTop--;
              } else {
                t1b = 0;
              }
              arr1numTop++;
              arr1numStack[arr1numTop] = fourFundamentalOperations(t1b, t1a, t1operator);
            } else {
              // 如果乘号和除号前面没有其他操作符，直接操作符入栈
              arr1operatorTop++;
              arr1operatorStack[arr1operatorTop] = arr1IN[i];
              break;
            }
          }
          break;
      }
    }
  }
  // 处理栈中的操作符
  while (arr1operatorTop > -1) {
    t1operator = arr1operatorStack[arr1operatorTop];
    arr1operatorTop--;
    t1a = arr1numStack[arr1numTop];
    arr1numTop--;
    t1b = arr1numStack[arr1numTop];
    arr1numTop--;
    arr1numTop++;
    arr1numStack[arr1numTop] = fourFundamentalOperations(t1b, t1a, t1operator);
  }
  printf("%f", arr1numStack[arr1numTop]);

  return 0;
}

float fourFundamentalOperations(float a, float b, char t1operator) {
  switch (t1operator) {
    case '+':
      return a + b;
    case '-':
      return a - b;
    case '*':
      return a * b;
    case '/':
      return a / b;
  }
  return 0;
}
