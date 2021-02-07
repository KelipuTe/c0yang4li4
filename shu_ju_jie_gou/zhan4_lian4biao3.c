#include <stdio.h>
#include <stdlib.h>

/*#####链表栈#####*/

// 栈结点
typedef struct ZhanJieDian
{
    // 结点数值
    int iShuZhi;
    // 下一个结点的指针
    struct ZhanJieDian *pNext;
} ZJD;

// 栈顶指针
ZJD *pZhanDing = NULL;

// 输出栈中元素
extern void shuChuZhan();
// 入栈
extern void ruZhan(int);
// 出栈
extern int chuZhan();

/*#####实现代码#####*/

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

void shuChuZhan()
{
    ZJD *tpZJD = NULL;

    if (pZhanDing == NULL)
    {
        printf("zhan4:kong1!\n");

        return;
    }
    tpZJD = pZhanDing;
    printf("zhan4:");
    while (tpZJD != NULL)
    {
        printf("%d,", tpZJD->iShuZhi);
        tpZJD = tpZJD->pNext;
    }
    printf("\n");
}

void ruZhan(int iShuZhi)
{
    ZJD *tpZJD = (ZJD *)malloc(sizeof(ZJD));

    tpZJD->iShuZhi = iShuZhi;
    printf("ru4zhan4:%d\n", iShuZhi);
    if (pZhanDing == NULL)
    {
        // 栈为空
        tpZJD->pNext = NULL;
        pZhanDing = tpZJD;
    }
    else
    {
        // 移动栈顶指针
        tpZJD->pNext = pZhanDing;
        pZhanDing = tpZJD;
    }
    shuChuZhan();
}

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