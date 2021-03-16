#include <stdio.h>
#include <stdlib.h>

/*#####链表#####*/

// 链表结点
typedef struct LianBiaoJieDian {
    // 数值
    int iShuZhi;
    // 下一个结点的指针
    struct LianBiaoJieDian *pLBJDNext;
} LBJD;

// 输出链表
extern void shuChuLianBiao(LBJD *);
// 添加结点
extern void tianJiaXiang(LBJD **, LBJD **, int);
// 移除指定结点
extern void yiChuXiang(LBJD **, LBJD **, int);

int main() {
    // 链表头指针，链表尾指针
    LBJD *pLBJDTou = NULL, *pLBJDWei = NULL;

    shuChuLianBiao(pLBJDTou);

    yiChuXiang(&pLBJDTou, &pLBJDWei, 3);

    tianJiaXiang(&pLBJDTou, &pLBJDWei, 1);
    tianJiaXiang(&pLBJDTou, &pLBJDWei, 3);
    tianJiaXiang(&pLBJDTou, &pLBJDWei, 4);
    tianJiaXiang(&pLBJDTou, &pLBJDWei, 3);
    tianJiaXiang(&pLBJDTou, &pLBJDWei, 4);

    shuChuLianBiao(pLBJDTou);

    yiChuXiang(&pLBJDTou, &pLBJDWei, 4);

    shuChuLianBiao(pLBJDTou);

    tianJiaXiang(&pLBJDTou, &pLBJDWei, 5);

    shuChuLianBiao(pLBJDTou);

    yiChuXiang(&pLBJDTou, &pLBJDWei, 1);

    shuChuLianBiao(pLBJDTou);

    return 0;
}

void shuChuLianBiao(LBJD *pLBJDTou) {
    LBJD *tpLBJD = pLBJDTou;

    printf("lian4biao3:");
    if (pLBJDTou != NULL) {
        // 注意空表
        while (tpLBJD != NULL) {
            printf("%d,", tpLBJD->iShuZhi);
            tpLBJD = tpLBJD->pLBJDNext;
        }
    }
    printf("\n");
}

void tianJiaXiang(LBJD **ppLBJDTou, LBJD **ppLBJDWei, int iShuZhi) {
    LBJD *tpLBJD = (LBJD *)malloc(sizeof(LBJD));

    tpLBJD->iShuZhi = iShuZhi;
    tpLBJD->pLBJDNext = NULL;
    if (*ppLBJDTou == NULL) {
        // 链表为空
        *ppLBJDTou = *ppLBJDWei = tpLBJD;
    } else {
        // 链表不为空，则把结点连接到链表尾部
        (*ppLBJDWei)->pLBJDNext = tpLBJD;
        *ppLBJDWei = tpLBJD;
    }
}

void yiChuXiang(LBJD **ppLBJDTou, LBJD **ppLBJDWei, int iShuZhi) {
    // 当前结点，上一个结点
    LBJD *tpLBJDNow = *ppLBJDTou, *tpLBJDLast = *ppLBJDTou;

    if (*ppLBJDTou != NULL) {
        while (tpLBJDNow != NULL) {
            if (tpLBJDNow->iShuZhi == iShuZhi) {
                if (tpLBJDNow == *ppLBJDTou) {
                    // 刚好是头
                    *ppLBJDTou = tpLBJDNow->pLBJDNext;
                    free(tpLBJDNow);
                    tpLBJDNow = *ppLBJDTou;
                } else if (tpLBJDNow == *ppLBJDWei) {
                    // 刚好是尾
                    tpLBJDLast->pLBJDNext = NULL;
                    *ppLBJDWei = tpLBJDLast;
                    free(tpLBJDNow);
                    tpLBJDNow = NULL;
                } else {
                    // 连接当前结点的前一个结点和后一个结点
                    tpLBJDLast->pLBJDNext = tpLBJDNow->pLBJDNext;
                    free(tpLBJDNow);
                    tpLBJDNow = tpLBJDLast->pLBJDNext;
                }
            } else {
                // 指针后移继续寻找
                tpLBJDLast = tpLBJDNow;
                tpLBJDNow = tpLBJDNow->pLBJDNext;
            }
        }
    }
}