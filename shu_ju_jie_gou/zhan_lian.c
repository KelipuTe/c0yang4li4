#include <stdio.h>
#include <stdlib.h>

/**
 * 栈结点
 */
struct ZhanJieDian
{
    // 数据域
    int num;
    // 下一个结点的指针
    struct ZhanJieDian *pNext;
};

// 栈顶指针
struct ZhanJieDian *pZhanDing = NULL;

extern void shuChuZhan();
extern void ruZhan(int);
extern int chuZhan();

/**
 * 链表栈
 */
int main()
{
    ruZhan(1);
    ruZhan(2);
    ruZhan(3);
    chuZhan();
    chuZhan();
    chuZhan();
    chuZhan();
    return 0;
}

/**
 * 输出栈中元素
 */
void shuChuZhan()
{
    struct ZhanJieDian *pTemp = NULL;
    
    if (pZhanDing == NULL)
    {
        printf("zhan4:kong1!\n");

        return;
    }
    pTemp = pZhanDing;
    printf("zhan4:");
    while (pTemp != NULL)
    {
        printf("%d,", pTemp->num);
        pTemp = pTemp->pNext;
    }
    printf("\n");
}

/**
 * 入栈
 */
void ruZhan(int num)
{
    struct ZhanJieDian *pTemp = (struct ZhanJieDian *)malloc(sizeof(struct ZhanJieDian));

    pTemp->num = num;
    printf("ru4zhan4:%d\n", num);
    if (pZhanDing == NULL)
    {
        // 栈顶指针为空
        pTemp->pNext = NULL;
        pZhanDing = pTemp;
    }
    else
    {
        // 移动栈顶指针
        pTemp->pNext = pZhanDing;
        pZhanDing = pTemp;
    }
    shuChuZhan();
}

/**
 * 出栈
 */
int chuZhan()
{
    struct ZhanJieDian *pNow = NULL;
    int num = 0;

    if (pZhanDing == NULL)
    {
        printf("zhan4:kong1!\n");

        return 0;
    }
    pNow = pZhanDing;
    num = pZhanDing->num;
    printf("chu1zhan4:%d\n", num);
    // 移动栈顶指针
    pZhanDing = pZhanDing->pNext;
    free(pNow);
    shuChuZhan();

    return num;
}