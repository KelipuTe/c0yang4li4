#include <stdio.h>
#include <stdlib.h>

/*#####链表队列#####*/

// 栈为空时输出的无效值
#define DUI_LIE_NULL -2147483648

// 队列结点
typedef struct DuiLieJieDian {
    // 结点数值
    int iShuZhi;
    // 下一个结点的指针
    struct DuiLieJieDian *pDLJDNext;
} DLJD;

// 输出队列元素
extern void shuChuDuiLie(DLJD *);
// 入队
extern void ruDui(DLJD **, DLJD **, int);
// 出队
extern int chuDui(DLJD **);

/*#####实现代码#####*/

int main() {
    // 队列头指针，队列尾指针
    DLJD *pDLJDTou = NULL, *pDLJDWei = NULL;

    ruDui(&pDLJDTou, &pDLJDWei, 1);

    chuDui(&pDLJDTou);
    chuDui(&pDLJDTou);

    ruDui(&pDLJDTou, &pDLJDWei, 2);
    ruDui(&pDLJDTou, &pDLJDWei, 3);

    shuChuDuiLie(pDLJDTou);

    chuDui(&pDLJDTou);
    chuDui(&pDLJDTou);
    chuDui(&pDLJDTou);

    return 0;
}

void shuChuDuiLie(DLJD *pDLJDTou) {
    DLJD *tpDLJD = pDLJDTou;

    printf("dui4lie4:");
    if (tpDLJD == NULL) {
        return;
    }
    while (tpDLJD != NULL) {
        printf("%d,", tpDLJD->iShuZhi);
        tpDLJD = tpDLJD->pDLJDNext;
    }
    printf("\n");
}

void ruDui(DLJD **ppDLJDTou, DLJD **ppDLJDWei, int iShuZhi) {
    DLJD *tpDLJD = (DLJD *)malloc(sizeof(DLJD));

    tpDLJD->iShuZhi = iShuZhi;
    tpDLJD->pDLJDNext = NULL;
    printf("ru4dui4:%d\n", iShuZhi);
    if (*ppDLJDTou == NULL) {
        // 队列为空
        *ppDLJDTou = *ppDLJDWei = tpDLJD;
    } else {
        // 移动队列尾指针
        (*ppDLJDWei)->pDLJDNext = tpDLJD;
        *ppDLJDWei = tpDLJD;
    }
}

int chuDui(DLJD **ppDLJDTou) {
    DLJD *pDLJDNow = *ppDLJDTou;
    int iShuZhi = DUI_LIE_NULL;

    if (pDLJDNow == NULL) {
        printf("kong1dui4lie4:%d\n", iShuZhi);
        return iShuZhi;
    }
    // 出队的元素
    iShuZhi = pDLJDNow->iShuZhi;
    printf("chu1dui4:%d\n", iShuZhi);
    // 移动队列头指针
    *ppDLJDTou = (*ppDLJDTou)->pDLJDNext;
    // 释放资源
    free(pDLJDNow);

    return iShuZhi;
}