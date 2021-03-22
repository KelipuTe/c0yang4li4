#include <stdio.h>

/*#####栈-后缀表达式#####*/

// 表达式长度
#define BIAO_DA_SHI_LEN 256

// 四则运算
extern float jiSuan(char, float, float);

int main() {
    // 中缀表达式
    // char sZhongZhui[BIAO_DA_SHI_LEN] = "(1-9)*(2+8)";
    char sZhongZhui[BIAO_DA_SHI_LEN] = "(-1-99)*(25+75)";
    // 操作数
    float fCaoZuoShu = -1, tfNum1 = 0, tfNum2 = 0, tfNum3 = 0;
    // 操作数栈
    float farrShuZhan[BIAO_DA_SHI_LEN] = {0};
    // 操作数栈顶
    int iShuZhanDing = 0;
    // 操作符
    char cCaoZuoFu;
    // 操作符栈
    char carrCaoZuoFuZhan[BIAO_DA_SHI_LEN] = {0};
    // 操作符栈顶
    int iCaoZuoFuZhanDing = 0;

    {
        int i = 0;
        while (sZhongZhui[i] != '\0') {
            if (sZhongZhui[i] >= '0' && sZhongZhui[i] <= '9') {
                // 处理数字
                if (fCaoZuoShu >= 0) {
                    fCaoZuoShu *= 10;
                    fCaoZuoShu += (int)(sZhongZhui[i] - '0');
                } else {
                    fCaoZuoShu = (int)(sZhongZhui[i] - '0');
                }
                i++;
                continue;
            } else {
                if (fCaoZuoShu >= 0) {
                    // 如果前面读到过有效的数字，就把数字入栈
                    farrShuZhan[iShuZhanDing++] = fCaoZuoShu;
                    fCaoZuoShu = -1;
                }
                // 处理操作符
                switch (sZhongZhui[i]) {
                    case '(':
                        carrCaoZuoFuZhan[iCaoZuoFuZhanDing++] = sZhongZhui[i];
                        break;
                    case ')':
                        while (1) {
                            // 遇到右括号时，持续输出操作符，直到匹配到左括号
                            cCaoZuoFu = carrCaoZuoFuZhan[--iCaoZuoFuZhanDing];
                            if (cCaoZuoFu == '(') {
                                break;
                            } else {
                                tfNum1 = farrShuZhan[--iShuZhanDing];
                                tfNum2 = farrShuZhan[--iShuZhanDing];
                                tfNum3 = jiSuan(cCaoZuoFu, tfNum2, tfNum1);
                                farrShuZhan[iShuZhanDing++] = tfNum3;
                            }
                        }
                        break;
                    case '+':
                    case '-':
                        while (1) {
                            // 如果加号和减号前面有其他操作符则需要输出
                            if (iCaoZuoFuZhanDing < 1) {
                                carrCaoZuoFuZhan[iCaoZuoFuZhanDing++] = sZhongZhui[i];
                                break;
                            } else {
                                cCaoZuoFu = carrCaoZuoFuZhan[iCaoZuoFuZhanDing - 1];
                                if (cCaoZuoFu == '+' || cCaoZuoFu == '-' || cCaoZuoFu == '*' || cCaoZuoFu == '/') {
                                    cCaoZuoFu = carrCaoZuoFuZhan[--iCaoZuoFuZhanDing];
                                    if (iShuZhanDing > 0) {
                                        tfNum1 = farrShuZhan[--iShuZhanDing];
                                    } else {
                                        tfNum1 = 0;
                                    }
                                    if (iShuZhanDing > 0) {
                                        tfNum2 = farrShuZhan[--iShuZhanDing];
                                    } else {
                                        tfNum2 = 0;
                                    }
                                    tfNum3 = jiSuan(cCaoZuoFu, tfNum2, tfNum1);
                                    farrShuZhan[iShuZhanDing++] = tfNum3;
                                } else {
                                    carrCaoZuoFuZhan[iCaoZuoFuZhanDing++] = sZhongZhui[i];
                                    break;
                                }
                            }
                        }
                        break;
                    case '*':
                    case '/':
                        while (1) {
                            // 如果乘号和除号前面有乘号或除号则需要输出，加号或减号则不输出
                            cCaoZuoFu = carrCaoZuoFuZhan[iCaoZuoFuZhanDing - 1];
                            if (cCaoZuoFu == '*' || cCaoZuoFu == '/') {
                                cCaoZuoFu = carrCaoZuoFuZhan[--iCaoZuoFuZhanDing];
                                if (iShuZhanDing > 0) {
                                    tfNum1 = farrShuZhan[--iShuZhanDing];
                                } else {
                                    tfNum1 = 0;
                                }
                                if (iShuZhanDing > 0) {
                                    tfNum2 = farrShuZhan[--iShuZhanDing];
                                } else {
                                    tfNum2 = 0;
                                }
                                tfNum3 = jiSuan(cCaoZuoFu, tfNum2, tfNum1);
                                farrShuZhan[iShuZhanDing++] = tfNum3;
                            } else {
                                carrCaoZuoFuZhan[iCaoZuoFuZhanDing++] = sZhongZhui[i];
                                break;
                            }
                        }
                        break;
                }
                i++;
            }
        }
        // 处理栈中的操作符
        while (iCaoZuoFuZhanDing > 0) {
            cCaoZuoFu = carrCaoZuoFuZhan[--iCaoZuoFuZhanDing];
            tfNum1 = farrShuZhan[--iShuZhanDing];
            tfNum2 = farrShuZhan[--iShuZhanDing];
            tfNum3 = jiSuan(cCaoZuoFu, tfNum2, tfNum1);
            farrShuZhan[iShuZhanDing++] = tfNum3;
        }
        printf("%f", farrShuZhan[--iShuZhanDing]);
    }
}

float jiSuan(char cCaoZuoFu, float tfNum1, float tfNum2) {
    switch (cCaoZuoFu) {
        case '+':
            return tfNum1 + tfNum2;
        case '-':
            return tfNum1 - tfNum2;
        case '*':
            return tfNum1 * tfNum2;
        case '/':
            return tfNum1 / tfNum2;
    }
    return 0.0;
}