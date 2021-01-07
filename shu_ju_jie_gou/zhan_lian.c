#include <stdio.h>
#include <stdlib.h>

struct JieDian
{
    int num;
    struct JieDian *pNext;
};

// 栈顶指针
struct JieDian *pDing;

extern void chuShiHua();
extern void shuChuZhan();
extern void ruZhan();
extern int chuZhan();

int main()
{
    chuShiHua();
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
void chuShiHua()
{
    pDing = NULL;
}

/**
 * 输出栈中元素
 */ 
void shuChuZhan()
{
    if (pDing == NULL)
    {
        printf("zhan4:kong1!\n");
        return;
    }
    struct JieDian *pTemp;
    pTemp = pDing;
    printf("zhan4:");
    while (pTemp != NULL)
    {
        printf("%d ", pTemp->num);
        pTemp = pTemp->pNext;
    }
    printf("\n");
}

/**
 * 入栈
 */ 
void ruZhan(int num)
{
    struct JieDian *pTemp = (struct JieDian *)malloc(sizeof(struct JieDian));
    pTemp->num = num;
    if (pDing == NULL)
    {
        pTemp->pNext = NULL;
        pDing = pTemp;
    }
    else
    {
        // 移动栈顶指针
        pTemp->pNext = pDing;
        pDing = pTemp;
    }
    shuChuZhan();
}

/**
 * 出栈
 */ 
int chuZhan()
{
    if (pDing == NULL)
    {
        printf("zhan4:kong1!\n");
        return -1;
    }
    struct JieDian *pNow;
    int num = pDing->num;
    pNow = pDing;
    // 移动栈顶指针
    pDing = pDing->pNext;
    free(pNow);
    printf("chu1zhan4:%d\n", num);
    shuChuZhan();
    return num;
}