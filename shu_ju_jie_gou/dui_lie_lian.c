#include <stdio.h>
#include <stdlib.h>

/**
 * 队列结点
 */
struct DuiLieJieDian
{
    // 数据域
    int num;
    // 下一个结点的指针
    struct DuiLieJieDian *pNext;
};

// 队列头指针
struct DuiLieJieDian *pDuiLieHead = NULL;
// 队列尾指针
struct DuiLieJieDian *pDuiLieTail = NULL;

extern void shuChuDuiLie();
extern void ruDui(int);
extern int chuDui();

/**
 * 链表队列
 */
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

/**
 * 输出队列元素
 */
void shuChuDuiLie()
{
    struct DuiLieJieDian *pTemp = NULL;
    
    if (pDuiLieHead == NULL)
    {
        printf("dui4lie4:kong1!\n");

        return;
    }
    pTemp = pDuiLieHead;
    printf("dui4lie4:");
    while (pTemp != NULL)
    {
        printf("%d,", pTemp->num);
        pTemp = pTemp->pNext;
    }
    printf("\n");
}

/**
 * 入队
 */
void ruDui(int num)
{
    struct DuiLieJieDian *pTemp = (struct DuiLieJieDian *)malloc(sizeof(struct DuiLieJieDian));

    pTemp->num = num;
    pTemp->pNext = NULL;
    printf("ru4dui4:%d\n", num);
    if (pDuiLieHead == NULL)
    {
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

/**
 * 出队
 */
int chuDui()
{
    struct DuiLieJieDian *pNow = NULL;
    int num = 0;

    if (pDuiLieHead == NULL)
    {
        printf("dui4lie4:kong1!\n");

        return 0;
    }
    pNow = pDuiLieHead;
    num = pDuiLieHead->num;
    printf("chu1dui4:%d\n", num);
    // 移动队列头指针
    pDuiLieHead = pDuiLieHead->pNext;
    free(pNow);
    shuChuDuiLie();

    return num;
}