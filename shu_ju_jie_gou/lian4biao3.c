#include <stdio.h>
#include <stdlib.h>

/*#####链表#####*/

// 链表结点
typedef struct LianBiaoJieDian
{
    // 数值
    int iShuZhi;
    // 下一个结点的指针
    struct LianBiaoJieDian *pNext;
} LBJD;

// 链表头指针
LBJD *pLianBiaoHead = NULL;
// 链表尾指针
LBJD *pLianBiaoTail = NULL;

// 输出链表
extern void shuChuLianBiao();
// 添加结点
extern void tianJiaXiang(int);
// 移除指定结点
extern void yiChuXiang();

int main()
{
    tianJiaXiang(1);
    tianJiaXiang(2);
    tianJiaXiang(3);
    tianJiaXiang(4);
    tianJiaXiang(3);
    tianJiaXiang(4);
    yiChuXiang(3);
    return 0;
}

void shuChuLianBiao()
{
    LBJD *tpLBJD = NULL;

    if (pLianBiaoHead == NULL)
    {
        printf("kong1lian4biao3!\n");

        return;
    }
    tpLBJD = pLianBiaoHead;
    printf("lian4biao3:");
    while (tpLBJD != NULL)
    {
        printf("%d,", tpLBJD->iShuZhi);
        tpLBJD = tpLBJD->pNext;
    }
    printf("\n");
}

void tianJiaXiang(int iShuZhi)
{
    // 申请内存
    LBJD *tpLBJD = (LBJD *)malloc(sizeof(LBJD));

    tpLBJD->iShuZhi = iShuZhi;
    tpLBJD->pNext = NULL;
    if (pLianBiaoHead == NULL)
    {
        // 链表为空
        pLianBiaoHead = tpLBJD;
        pLianBiaoTail = tpLBJD;
    }
    else
    {
        // 把结点连接到链表尾部
        pLianBiaoTail->pNext = tpLBJD;
        pLianBiaoTail = tpLBJD;
    }
    shuChuLianBiao();
}

void yiChuXiang(int iShuZhi)
{
    // 当前结点
    LBJD *pNow;
    // 上一个结点
    LBJD *pLast;

    if (pLianBiaoHead == NULL)
    {
        return;
    }
    pLast = pNow = pLianBiaoHead;
    while (pNow != NULL)
    {
        if (pNow->iShuZhi == iShuZhi)
        {
            if (pNow == pLianBiaoHead)
            {
                // 刚好是头
                pLianBiaoHead = pNow->pNext;
                free(pNow);
                pNow = pLianBiaoHead;
            }
            else if (pNow == pLianBiaoTail)
            {
                // 刚好是尾
                pLast->pNext = NULL;
                pLianBiaoTail = pLast;
                free(pNow);
                pNow = NULL;
            }
            else
            {
                // 连接当前结点的前一个结点和后一个结点
                pLast->pNext = pNow->pNext;
                free(pNow);
                pNow = pLast->pNext;
            }
        }
        else
        {
            // 指针后移继续寻找
            pLast = pNow;
            pNow = pNow->pNext;
        }
    }
    shuChuLianBiao();
}