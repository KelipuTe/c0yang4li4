#include <stdio.h>
#include <stdlib.h>

/**
 * 链表结点
 */
struct LianBiaoJieDian
{
    // 数据域
    int num;
    // 下一个结点的指针
    struct LianBiaoJieDian *pNext;
};

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
    struct LianBiaoJieDian *pTemp = NULL;
    if (pLianBiaoHead == NULL)
    {
        printf("kong1lian4biao3!\n");

        return;
    }
    pTemp = pLianBiaoHead;
    printf("lian4biao3:");
    while (pTemp != NULL)
    {
        printf("%d,", pTemp->num);
        pTemp = pTemp->pNext;
    }
    printf("\n");
}

/**
 * 添加结点
 */
void tianJiaXiang(int num)
{
    // 申请内存
    struct LianBiaoJieDian *pTemp = (struct LianBiaoJieDian *)malloc(sizeof(struct LianBiaoJieDian));

    pTemp->num = num;
    pTemp->pNext = NULL;
    if (pLianBiaoHead == NULL)
    {
        // 头指针为空
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
void yiChuXiang(int num)
{
    // 当前结点
    struct LianBiaoJieDian *pNow;
    // 上一个结点
    struct LianBiaoJieDian *pLast;

    if (pLianBiaoHead == NULL)
    {
        return;
    }
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
                // 连接当前结点的前一个结点和后一个结点
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