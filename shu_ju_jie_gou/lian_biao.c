#include <stdio.h>
#include <stdlib.h>

/**
 * 链表节点
 */
struct LianBiaoJieDian
{
    // 数据域
    int num;
    // 指针域
    struct LianBiaoJieDian *pNext;
};

// 链表头指针
struct LianBiaoJieDian *pLianBiaoHead;
// 链表尾指针
struct LianBiaoJieDian *pLianBiaoTail;

extern void chuShiHua();
extern void shuChuLianBiao();
extern void tianJiaXiang(int);
extern void yiChuXiang();

/**
 * 链表
 */
int main()
{
    chuShiHua();
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
 * 初始化
 */
void chuShiHua()
{
    pLianBiaoHead = NULL;
    pLianBiaoTail = NULL;
}

/**
 * 输出链表
 */
void shuChuLianBiao()
{
    if (pLianBiaoHead == NULL)
    {
        printf("kong1lian4biao3!\n");
        return;
    }
    struct LianBiaoJieDian *pTemp = pLianBiaoHead;
    printf("lian4biao3:");
    while (pTemp != NULL)
    {
        printf("%d,", pTemp->num);
        pTemp = pTemp->pNext;
    }
    printf("\n");
}

/**
 * 添加节点
 */
void tianJiaXiang(int num)
{
    // 申请内存
    struct LianBiaoJieDian *pTemp = (struct LianBiaoJieDian *)malloc(sizeof(struct LianBiaoJieDian));
    pTemp->num = num;
    pTemp->pNext = NULL;
    if (pLianBiaoHead == NULL)
    {
        pLianBiaoHead = pTemp;
        pLianBiaoTail = pTemp;
    }
    else
    {
        pLianBiaoTail->pNext = pTemp;
        pLianBiaoTail = pTemp;
    }
    shuChuLianBiao();
}

/**
 * 移除指定节点
 */
void yiChuXiang(int num)
{
    if (pLianBiaoHead == NULL)
    {
        return;
    }
    struct LianBiaoJieDian *pNow;
    struct LianBiaoJieDian *pLast;
    pLast = pNow = pLianBiaoHead;
    while (pNow != NULL)
    {
        if (pNow->num == num)
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
                pLast->pNext = pNow->pNext;
                free(pNow);
                pNow = pLast->pNext;
            }
        }
        else
        {
            pLast = pNow;
            pNow = pNow->pNext;
        }
    }
    shuChuLianBiao();
}