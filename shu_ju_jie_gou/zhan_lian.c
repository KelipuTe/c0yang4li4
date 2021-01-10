#include <stdio.h>
#include <stdlib.h>

/**
 * 栈节点
 */
struct ZhanJieDian
{
    int num;
    struct ZhanJieDian *pNext;
};

// 栈顶指针
struct ZhanJieDian *pZhanDing;

extern void chuShiHuaZhan();
extern void shuChuZhan();
extern void ruZhan(int);
extern int chuZhan();

/**
 * 链表栈
 */
int main()
{
    chuShiHuaZhan();
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
 * 初始化
 */
void chuShiHuaZhan()
{
    pZhanDing = NULL;
}

/**
 * 输出栈中元素
 */
void shuChuZhan()
{
    if (pZhanDing == NULL)
    {
        printf("zhan4:kong1!\n");
        return;
    }
    struct ZhanJieDian *pTemp = pZhanDing;
    printf("zhan4:");
    while (pTemp != NULL)
    {
        printf("%d,", pTemp->num);
        pTemp = pTemp->pNext;
    }
    printf("\n");
}

/**
 * 入栈
 */
void ruZhan(int num)
{
    struct ZhanJieDian *pTemp = (struct ZhanJieDian *)malloc(sizeof(struct ZhanJieDian));
    pTemp->num = num;
    printf("ru4zhan4:%d\n", num);
    if (pZhanDing == NULL)
    {
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
    if (pZhanDing == NULL)
    {
        printf("zhan4:kong1!\n");
        return 0;
    }
    struct ZhanJieDian *pNow = pZhanDing;
    int num = pZhanDing->num;
    printf("chu1zhan4:%d\n", num);
    // 移动栈顶指针
    pZhanDing = pZhanDing->pNext;
    free(pNow);
    shuChuZhan();
    return num;
}