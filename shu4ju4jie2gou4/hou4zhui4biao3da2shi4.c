#include <stdio.h>

/*#####后缀表达式#####*/

// 表达式长度
#define BIAO_DA_SHI_LEN 256

// 中缀表达式转后缀表达式
extern void zhongZhuiZhuanHouZhui();
// 后缀表达式计算结果
extern float jiSuanHouZhui(char *);

/*#####实现代码#####*/

int main() {
    char sZhongZhui[BIAO_DA_SHI_LEN] = "(1-9)*(2+8)";
    char sHouZhui[BIAO_DA_SHI_LEN];

    printf("%s\n", sZhongZhui);
    zhongZhuiZhuanHouZhui(&sZhongZhui, &sHouZhui);
    printf("%s\n", sHouZhui);
    printf("%f\n", jiSuanHouZhui(&sHouZhui));
}

void zhongZhuiZhuanHouZhui(char *sZhongZhui, char *sHouZhui) {
    char cCaoZuoXiang;
    char cCaoZuoFu;
    // 操作符栈
    char carrCaoZuoFuZhan[BIAO_DA_SHI_LEN] = {0};
    int iCaoZuoFuZhanDing = 0;

    int j = 0;
    for (int i = 0; sZhongZhui[i] != '\0'; i++) {
        cCaoZuoXiang = sZhongZhui[i];
        if (cCaoZuoXiang >= '0' && cCaoZuoXiang <= '9') {
            // 处理数字
            sHouZhui[j++] = cCaoZuoXiang;
        } else {
            // 处理操作符
            switch (cCaoZuoXiang) {
                case '(':
                    carrCaoZuoFuZhan[iCaoZuoFuZhanDing++] = cCaoZuoXiang;
                    break;
                case ')':
                    while (1) {
                        // 遇到右括号时，持续输出操作符，直到匹配到左括号
                        cCaoZuoFu = carrCaoZuoFuZhan[--iCaoZuoFuZhanDing];
                        if (cCaoZuoFu == '(') {
                            break;
                        }
                        sHouZhui[j++] = cCaoZuoFu;
                    }
                    break;
                case '+':
                case '-':
                    while (1) {
                        // 如果加号和减号前面有其他操作符则需要输出
                        if (iCaoZuoFuZhanDing < 1) {
                            carrCaoZuoFuZhan[iCaoZuoFuZhanDing++] = cCaoZuoXiang;
                            break;
                        }
                        cCaoZuoFu = carrCaoZuoFuZhan[iCaoZuoFuZhanDing - 1];
                        if (cCaoZuoFu == '+' || cCaoZuoFu == '-' || cCaoZuoFu == '*' || cCaoZuoFu == '/') {
                            cCaoZuoFu = carrCaoZuoFuZhan[--iCaoZuoFuZhanDing];
                            sHouZhui[j++] = cCaoZuoFu;
                        } else {
                            carrCaoZuoFuZhan[iCaoZuoFuZhanDing++] = cCaoZuoXiang;
                            break;
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
                            sHouZhui[j++] = cCaoZuoFu;
                        } else {
                            carrCaoZuoFuZhan[iCaoZuoFuZhanDing++] = cCaoZuoXiang;
                            break;
                        }
                    }
                    break;
            }
        }
    }
    // 把栈中操作符全部输出
    // 注意这里用的是字符数组，所以要加\0
    while (1) {
        cCaoZuoFu = carrCaoZuoFuZhan[--iCaoZuoFuZhanDing];
        if (cCaoZuoFu == '\0') {
            break;
        }
        sHouZhui[j++] = cCaoZuoFu;
    }
    sHouZhui[j] = '\0';
}

float jiSuanHouZhui(char *sHouZhui) {
    char cCaoZuoXiang;
    float fNum1 = 0, fNum2 = 0, fNum3 = 0;
    // 操作项栈
    char carrCaoZuoXiangZhan[BIAO_DA_SHI_LEN] = {0};
    int iCaoZuoXiangZhanDing = 0;

    // 每次从栈中取两个数字，将计算的结果再入栈
    // 最后栈中的那个数字就是结果
    for (int i = 0; sHouZhui[i] != '\0'; i++) {
        cCaoZuoXiang = sHouZhui[i];
        if (cCaoZuoXiang >= '0' && cCaoZuoXiang <= '9') {
            // 处理数字，因为这里只考虑了10以内的四则运算，所以可以直接使用字符相减
            carrCaoZuoXiangZhan[iCaoZuoXiangZhanDing++] = (float)(cCaoZuoXiang - '0');
            continue;
        }
        switch (cCaoZuoXiang) {
            case '+':
                fNum1 = carrCaoZuoXiangZhan[--iCaoZuoXiangZhanDing];
                if (iCaoZuoXiangZhanDing < 1) {
                    fNum2 = 0;
                } else {
                    fNum2 = carrCaoZuoXiangZhan[--iCaoZuoXiangZhanDing];
                }
                fNum3 = fNum2 + fNum1;
                carrCaoZuoXiangZhan[iCaoZuoXiangZhanDing++] = fNum3;
                break;
            case '-':
                fNum1 = carrCaoZuoXiangZhan[--iCaoZuoXiangZhanDing];
                if (iCaoZuoXiangZhanDing < 1) {
                    fNum2 = 0;
                } else {
                    fNum2 = carrCaoZuoXiangZhan[--iCaoZuoXiangZhanDing];
                }
                fNum3 = fNum2 - fNum1;
                carrCaoZuoXiangZhan[iCaoZuoXiangZhanDing++] = fNum3;
                break;
            case '*':
                fNum1 = carrCaoZuoXiangZhan[--iCaoZuoXiangZhanDing];
                if (iCaoZuoXiangZhanDing < 1) {
                    fNum2 = 1;
                } else {
                    fNum2 = carrCaoZuoXiangZhan[--iCaoZuoXiangZhanDing];
                }
                fNum3 = fNum2 * fNum1;
                carrCaoZuoXiangZhan[iCaoZuoXiangZhanDing++] = fNum3;
                break;
            case '/':
                fNum1 = carrCaoZuoXiangZhan[--iCaoZuoXiangZhanDing];
                if (iCaoZuoXiangZhanDing < 1) {
                    fNum3 = fNum1;
                } else {
                    fNum2 = carrCaoZuoXiangZhan[--iCaoZuoXiangZhanDing];
                    fNum3 = fNum2 / fNum1;
                }
                carrCaoZuoXiangZhan[iCaoZuoXiangZhanDing++] = fNum3;
                ;
                break;
        }
    }

    return carrCaoZuoXiangZhan[--iCaoZuoXiangZhanDing];
}