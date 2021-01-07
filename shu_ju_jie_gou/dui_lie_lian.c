#include <stdio.h>
#include <stdlib.h>

struct JieDian
{
    int num;
    struct JieDian *pNext;
};

// 队列头指针
struct JieDian *pHead;
// 队列尾指针
struct JieDian *pTail;

extern void chuShiHua();
extern void shuChuDuiLie();
extern void ruDui();
extern int chuDui();

int main()
{
    chuShiHua();
    ruDui(1);
    ruDui(2);
    ruDui(3);
    chuDui();
    chuDui();
    chuDui();
    chuDui();
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
 * 输出队列元素
 */
void shuChuDuiLie()
{
    if (pHead == NULL)
    {
        printf("dui4lie4:kong1!\n");
        return;
    }
    struct JieDian *pTemp;
    pTemp = pHead;
    printf("dui4lie4:");
    while (pTemp != NULL)
    {
        printf("%d ", pTemp->num);
        pTemp = pTemp->pNext;
    }
    printf("\n");
}

/**
 * 入队
 */
void ruDui(int num)
{
    struct JieDian *pTemp = (struct JieDian *)malloc(sizeof(struct JieDian));
    pTemp->num = num;
    pTemp->pNext = NULL;
    if (pHead == NULL)
    {
        pHead = pTail = pTemp;
    }
    else
    {
        // 移动队列尾指针
        pTail->pNext = pTemp;
        pTail = pTail->pNext;
    }
    shuChuDuiLie();
}

/**
 * 出队
 */
int chuDui()
{
    if (pHead == NULL)
    {
        printf("dui4lie4:kong1!\n");
        return -1;
    }
    struct JieDian *pNow;
    int num = pHead->num;
    pNow = pHead;
    // 移动队列头指针
    pHead = pHead->pNext;
    free(pNow);
    printf("chu1dui5:%d\n", num);
    shuChuDuiLie();
    return num;
}