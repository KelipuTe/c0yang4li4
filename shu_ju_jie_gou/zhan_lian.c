#include <stdio.h>
#include <stdlib.h>

/**
 * 栈结点
 */
typedef struct ZhanJieDian
{
    // 数值
    int iShuZhi;
    // 下一个结点的指针
    struct ZhanJieDian *pNext;
} ZJD;

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
    ZJD *pTemp = NULL;

    if (pZhanDing == NULL)
    {
        printf("zhan4:kong1!\n");

        return;
    }
    pTemp = pZhanDing;
    printf("zhan4:");
    while (pTemp != NULL)
    {
        printf("%d,", pTemp->iShuZhi);
        pTemp = pTemp->pNext;
    }
    printf("\n");
}

/**
 * 入栈
 */
void ruZhan(int iShuZhi)
{
    ZJD *pTemp = (ZJD *)malloc(sizeof(ZJD));

    pTemp->iShuZhi = iShuZhi;
    printf("ru4zhan4:%d\n", iShuZhi);
    if (pZhanDing == NULL)
    {
        // 栈为空
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
    ZJD *pNow = NULL;
    int iShuZhi = 0;

    if (pZhanDing == NULL)
    {
        printf("zhan4:kong1!\n");

        return 0;
    }
    // 出栈的元素
    pNow = pZhanDing;
    iShuZhi = pZhanDing->iShuZhi;
    printf("chu1zhan4:%d\n", iShuZhi);
    // 移动栈顶指针
    pZhanDing = pZhanDing->pNext;
    // 释放资源
    free(pNow);
    shuChuZhan();

    return iShuZhi;
}