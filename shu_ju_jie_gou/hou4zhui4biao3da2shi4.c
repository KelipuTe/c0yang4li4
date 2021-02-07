#include <stdio.h>
#include <stdlib.h>

/*#####后缀表达式#####*/

// 中缀表达式转后缀表达式
extern void zhongZhuiZhuanHouZhui();
// 后缀表达式计算结果
extern float jiSuanHouZhuiBiaoDaShi(char *);

/*#####栈-字符#####*/

struct ZhanJieDian
{
    // 操作符
    char caoZuoFu;
    struct ZhanJieDian *pNext;
};

struct ZhanJieDian *pZhanDing = NULL;

extern void ruZhan(char);
extern char chuZhan();
extern char yuChuZhan();

/*#####栈-数值#####*/

struct ZhanJieDian2
{
    // 数值
    float num;
    struct ZhanJieDian2 *pNext;
};

struct ZhanJieDian2 *pZhanDing2 = NULL;

extern void ruZhan2(float);
extern float chuZhan2();

/*#####实现代码#####*/

int main()
{
    char zhongZhuiArr[] = "(1-9)*(2+8)";
    char houZhuiArr[32];
    float num = 0;

    printf("%s\n", zhongZhuiArr);
    zhongZhuiZhuanHouZhui(&zhongZhuiArr, &houZhuiArr);
    printf("%s\n", houZhuiArr);
    num = jiSuanHouZhuiBiaoDaShi(&houZhuiArr);
    printf("%f\n", num);
}

void zhongZhuiZhuanHouZhui(char *zhongZhuiArr, char *houZhuiArr)
{
    char caoZuoXiang;
    char tCaoZuoFu;

    int j = 0;
    for (int i = 0; zhongZhuiArr[i] != '\0'; i++)
    {
        caoZuoXiang = zhongZhuiArr[i];
        if (caoZuoXiang >= '0' && caoZuoXiang <= '9')
        {
            // 处理数字
            houZhuiArr[j++] = caoZuoXiang;
        }
        else
        {
            // 处理操作符
            switch (caoZuoXiang)
            {
            case '(':
                ruZhan(caoZuoXiang);
                break;
            case ')':
                while (1)
                {
                    // 遇到右括号时，持续输出操作符，直到匹配到左括号
                    tCaoZuoFu = chuZhan();
                    if (tCaoZuoFu == '(')
                    {
                        break;
                    }
                    houZhuiArr[j++] = tCaoZuoFu;
                }
                break;
            case '+':
            case '-':
                while (1)
                {
                    // 如果加号和减号前面有其他操作符则需要输出
                    tCaoZuoFu = yuChuZhan();
                    if (tCaoZuoFu == '+' || tCaoZuoFu == '-' || tCaoZuoFu == '*' || tCaoZuoFu == '/')
                    {
                        tCaoZuoFu = chuZhan();
                        houZhuiArr[j++] = tCaoZuoFu;
                    }
                    else
                    {
                        ruZhan(caoZuoXiang);
                        break;
                    }
                }
                break;
            case '*':
            case '/':
                while (1)
                {
                    // 如果乘号和除号前面有乘号或除号则需要输出，加号或减号则不输出
                    tCaoZuoFu = yuChuZhan();
                    if (tCaoZuoFu == '*' || tCaoZuoFu == '/')
                    {
                        tCaoZuoFu = chuZhan();
                        houZhuiArr[j++] = tCaoZuoFu;
                    }
                    else
                    {
                        ruZhan(caoZuoXiang);
                        break;
                    }
                }
                break;
            }
        }
    }
    // 把栈中操作符全部输出
    // 注意这里用的是字符数组，所以要加\0
    while (1)
    {
        tCaoZuoFu = chuZhan();
        if (tCaoZuoFu == '\0')
        {
            break;
        }
        houZhuiArr[j++] = tCaoZuoFu;
    }
    houZhuiArr[j] = '\0';
}

float jiSuanHouZhuiBiaoDaShi(char *houZhuiArr)
{
    char caoZuoXiang;
    float num1 = 0, num2 = 0, num3 = 0;
    // 每次从栈中取两个数字，将计算的结果再入栈
    // 最后栈中的那个数字就是结果
    for (int i = 0; houZhuiArr[i] != '\0'; i++)
    {
        caoZuoXiang = houZhuiArr[i];
        if (caoZuoXiang >= '0' && caoZuoXiang <= '9')
        {
            // 处理数字，因为这里只考虑了10以内的四则运算，所以可以直接使用字符相减
            ruZhan2((float)(caoZuoXiang - '0'));
            continue;
        }
        switch (caoZuoXiang)
        {
        case '+':
            num1 = chuZhan2();
            num2 = chuZhan2();
            num3 = num2 + num1;
            ruZhan2(num3);
            break;
        case '-':
            num1 = chuZhan2();
            num2 = chuZhan2();
            num3 = num2 - num1;
            ruZhan2(num3);
            break;
        case '*':
            num1 = chuZhan2();
            num2 = chuZhan2();
            num3 = num2 * num1;
            ruZhan2(num3);
            break;
        case '/':
            num1 = chuZhan2();
            num2 = chuZhan2();
            num3 = num2 / num1;
            ruZhan2(num3);
            break;
        }
    }
    return chuZhan2();
}

/*#####栈-字符#####*/

void ruZhan(char caoZuoFu)
{
    struct ZhanJieDian *pTemp = (struct ZhanJieDian *)malloc(sizeof(struct ZhanJieDian));

    pTemp->caoZuoFu = caoZuoFu;
    if (pZhanDing == NULL)
    {
        pTemp->pNext = NULL;
        pZhanDing = pTemp;
    }
    else
    {
        pTemp->pNext = pZhanDing;
        pZhanDing = pTemp;
    }
}

char chuZhan()
{
    char caoZuoFu = '\0';
    struct ZhanJieDian *pNow = NULL;

    if (pZhanDing == NULL)
    {
        return caoZuoFu;
    }
    pNow = pZhanDing;
    caoZuoFu = pZhanDing->caoZuoFu;
    pZhanDing = pZhanDing->pNext;
    free(pNow);

    return caoZuoFu;
}

/**
 * 预出栈，只获取元素，不出栈
 */
char yuChuZhan()
{
    char caoZuoFu = '\0';
    if (pZhanDing == NULL)
    {
        return caoZuoFu;
    }
    caoZuoFu = pZhanDing->caoZuoFu;

    return caoZuoFu;
}

/*#####栈-数值#####*/

void ruZhan2(float num)
{
    struct ZhanJieDian2 *pTemp = (struct ZhanJieDian2 *)malloc(sizeof(struct ZhanJieDian2));

    pTemp->num = num;
    if (pZhanDing2 == NULL)
    {
        pTemp->pNext = NULL;
        pZhanDing2 = pTemp;
    }
    else
    {
        pTemp->pNext = pZhanDing2;
        pZhanDing2 = pTemp;
    }
}

float chuZhan2()
{
    float num = 0;
    if (pZhanDing2 == NULL)
    {
        return num;
    }
    struct ZhanJieDian2 *pNow = pZhanDing2;
    num = pZhanDing2->num;
    pZhanDing2 = pZhanDing2->pNext;
    free(pNow);

    return num;
}