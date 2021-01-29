#include <stdio.h>
#include <stdlib.h>

/*#####链表队列#####*/

// 队列结点
typedef struct DuiLieJieDian
{
    // 结点数值
    int iShuZhi;
    // 下一个结点的指针
    struct DuiLieJieDian *pNext;
} DLJD;

// 队列头指针
DLJD *pDuiLieHead = NULL;
// 队列尾指针
DLJD *pDuiLieTail = NULL;

// 输出队列元素
extern void shuChuDuiLie();
// 入队
extern void ruDui(int);
// 出队
extern int chuDui();



int main()
{
    ruDui(1);
    ruDui(2);
    chuDui();
    ruDui(3);
    chuDui();
    chuDui();
    chuDui();

    return 0;
}

void shuChuDuiLie()
{
    DLJD *pTemp = NULL;

    if (pDuiLieHead == NULL)
    {
        printf("dui4lie4:kong1!\n");

        return;
    }
    pTemp = pDuiLieHead;
    printf("dui4lie4:");
    while (pTemp != NULL)
    {
        printf("%d,", pTemp->iShuZhi);
        pTemp = pTemp->pNext;
    }
    printf("\n");
}

void ruDui(int iShuZhi)
{
    DLJD *pTemp = (DLJD *)malloc(sizeof(DLJD));

    pTemp->iShuZhi = iShuZhi;
    pTemp->pNext = NULL;
    printf("ru4dui4:%d\n", iShuZhi);
    if (pDuiLieHead == NULL)
    {
        // 队列为空
        pDuiLieHead = pDuiLieTail = pTemp;
    }
    else
    {
        // 移动队列尾指针
        pDuiLieTail->pNext = pTemp;
        pDuiLieTail = pDuiLieTail->pNext;
    }
    shuChuDuiLie();
}

int chuDui()
{
    DLJD *pNow = NULL;
    int iShuZhi = 0;

    if (pDuiLieHead == NULL)
    {
        printf("dui4lie4:kong1!\n");

        return 0;
    }
    // 出队的元素
    pNow = pDuiLieHead;
    iShuZhi = pDuiLieHead->iShuZhi;
    printf("chu1dui4:%d\n", iShuZhi);
    // 移动队列头指针
    pDuiLieHead = pDuiLieHead->pNext;
    // 释放资源
    free(pNow);
    shuChuDuiLie();

    return iShuZhi;
}