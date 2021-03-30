#include <stdio.h>
#include <stdlib.h>

/*#####链表-栈#####*/

// 栈为空时输出的无效值
#define ZHAN_NULL -2147483648

// 栈结点
typedef struct ZhanJieDian {
    // 结点数值
    int iShuZhi;
    // 下一个结点的指针
    struct ZhanJieDian *pZJDNext;
} ZJD;

// 输出栈中元素
extern void shuChuZhan(ZJD *);
// 入栈
extern void ruZhan(ZJD **, int);
// 出栈
extern int chuZhan(ZJD **);

/*#####实现代码#####*/

int main() {
    // 栈顶指针
    ZJD *pZJDZhanDing = NULL;

    ruZhan(&pZJDZhanDing, 1);

    chuZhan(&pZJDZhanDing);
    chuZhan(&pZJDZhanDing);

    ruZhan(&pZJDZhanDing, 2);
    ruZhan(&pZJDZhanDing, 3);

    shuChuZhan(pZJDZhanDing);

    chuZhan(&pZJDZhanDing);
    chuZhan(&pZJDZhanDing);
    chuZhan(&pZJDZhanDing);

    return 0;
}

void shuChuZhan(ZJD *pZJDZhanDing) {
    ZJD *tpZJD = pZJDZhanDing;

    printf("zhan4:");
    if (tpZJD == NULL) {
        return;
    }
    while (tpZJD != NULL) {
        printf("%d,", tpZJD->iShuZhi);
        tpZJD = tpZJD->pZJDNext;
    }
    printf("\n");
}

void ruZhan(ZJD **ppZJDZhanDing, int iShuZhi) {
    ZJD *tpZJD = (ZJD *)malloc(sizeof(ZJD));

    tpZJD->iShuZhi = iShuZhi;
    printf("ru4zhan4:%d\n", iShuZhi);
    if (*ppZJDZhanDing == NULL) {
        // 栈为空
        tpZJD->pZJDNext = NULL;
        *ppZJDZhanDing = tpZJD;
    } else {
        // 移动栈顶指针
        tpZJD->pZJDNext = *ppZJDZhanDing;
        *ppZJDZhanDing = tpZJD;
    }
}

int chuZhan(ZJD **ppZJDZhanDing) {
    ZJD *pZJDNow = *ppZJDZhanDing;
    int iShuZhi = ZHAN_NULL;

    if (*ppZJDZhanDing == NULL) {
        printf("kong1zhan4:%d\n", iShuZhi);
        return iShuZhi;
    }
    // 出栈的元素
    iShuZhi = pZJDNow->iShuZhi;
    printf("chu1zhan4:%d\n", iShuZhi);
    // 移动栈顶指针
    *ppZJDZhanDing = (*ppZJDZhanDing)->pZJDNext;
    // 释放资源
    free(pZJDNow);

    return iShuZhi;
}