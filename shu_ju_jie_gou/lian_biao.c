#include <stdio.h>
#include <stdlib.h>

struct JieDian
{
    // 数据域
    int num;
    // 指针域
    struct JieDian *pNext;
};

// 头指针
struct JieDian *pHead;
// 尾指针
struct JieDian *pTail;

extern void chuShiHua();
extern void shuChuLianBiao();
extern void tianJiaXiang();
extern void yiChuXiang();

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
    pHead = NULL;
    pTail = NULL;
}

/**
 * 输出链表
 */
void shuChuLianBiao()
{
    if (pHead == NULL)
    {
        printf("kong1lian4biao3!\n");
        return;
    }
    struct JieDian *pTemp;
    pTemp = pHead;
    while (pTemp != NULL)
    {
        printf("%d ", pTemp->num);
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
    struct JieDian *pTemp = (struct JieDian *)malloc(sizeof(struct JieDian));
    pTemp->num = num;
    pTemp->pNext = NULL;
    if (pHead == NULL)
    {
        pHead = pTemp;
        pTail = pTemp;
    }
    else
    {
        pTail->pNext = pTemp;
        pTail = pTemp;
    }
    shuChuLianBiao();
}

/**
 * 移除指定节点
 */
void yiChuXiang(int num)
{
    if (pHead == NULL)
    {
        return;
    }
    struct JieDian *pNow;
    struct JieDian *pLast;
    pLast = pNow = pHead;
    while (pNow != NULL)
    {
        if (pNow->num == num)
        {
            if (pNow == pHead)
            {
                // 刚好是头
                pHead = pNow->pNext;
                free(pNow);
                pNow = pHead;
            }
            else if (pNow == pTail)
            {
                // 刚好是尾
                pLast->pNext = NULL;
                pTail = pLast;
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