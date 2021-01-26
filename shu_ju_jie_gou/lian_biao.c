#include <stdio.h>
#include <stdlib.h>

/**
 * 链表结点
 */
typedef struct LianBiaoJieDian
{
    // 数值
    int iShuZhi;
    // 下一个结点的指针
    struct LianBiaoJieDian *pNext;
} LBJD;

// 链表头指针
struct LianBiaoJieDian *pLianBiaoHead = NULL;
// 链表尾指针
struct LianBiaoJieDian *pLianBiaoTail = NULL;

extern void shuChuLianBiao();
extern void tianJiaXiang(int);
extern void yiChuXiang();

/**
 * 链表
 */
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

/**
 * 输出链表
 */
void shuChuLianBiao()
{
    LBJD *pTemp = NULL;

    if (pLianBiaoHead == NULL)
    {
        printf("kong1lian4biao3!\n");

        return;
    }
    pTemp = pLianBiaoHead;
    printf("lian4biao3:");
    while (pTemp != NULL)
    {
        printf("%d,", pTemp->iShuZhi);
        pTemp = pTemp->pNext;
    }
    printf("\n");
}

/**
 * 添加结点
 */
void tianJiaXiang(int iShuZhi)
{
    // 申请内存
    LBJD *pTemp = (LBJD *)malloc(sizeof(LBJD));

    pTemp->iShuZhi = iShuZhi;
    pTemp->pNext = NULL;
    if (pLianBiaoHead == NULL)
    {
        // 链表为空
        pLianBiaoHead = pTemp;
        pLianBiaoTail = pTemp;
    }
    else
    {
        // 把结点连接到链表尾部
        pLianBiaoTail->pNext = pTemp;
        pLianBiaoTail = pTemp;
    }
    shuChuLianBiao();
}

/**
 * 移除指定结点
 */
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