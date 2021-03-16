#include <stdio.h>
#include <stdlib.h>

/*#####循环链表-约瑟夫问题#####*/

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
// 约瑟夫问题
extern void yueSeFuWenTi(LBJD **, LBJD **, int);

/*#####实现代码#####*/

int main() {
    // 链表头指针，链表尾指针
    LBJD *pLBJDTou = NULL, *pLBJDWei = pLBJDTou;
    // 人数，kill数
    int iNum = 41, iKill = iNum - 2;

    for (int ii = 1; ii <= iNum; ii++) {
        tianJiaXiang(&pLBJDTou, &pLBJDWei, ii);
    }

    shuChuLianBiao(pLBJDTou);

    yueSeFuWenTi(&pLBJDTou, &pLBJDWei, iKill);

    shuChuLianBiao(pLBJDTou);

    return 0;
}

void shuChuLianBiao(LBJD *pLBJDTou) {
    LBJD *tpLBJD = pLBJDTou;

    printf("lian4biao3:");
    if (pLBJDTou != NULL) {
        // 注意空表
        int ibStart = 0;
        while (!(ibStart == 1 && tpLBJD == pLBJDTou)) {
            // 当遍历开始并且又一次回到头指针时，遍历结束
            ibStart = 1;
            printf("%d,", tpLBJD->iShuZhi);
            tpLBJD = tpLBJD->pLBJDNext;
        }
    }
    printf("\n");
}

void tianJiaXiang(LBJD **ppLBJDTou, LBJD **ppLBJDWei, int iShuZhi) {
    LBJD *tpLBJD = (LBJD *)malloc(sizeof(LBJD));

    tpLBJD->iShuZhi = iShuZhi;
    // 新的结点的指针域放头指针
    tpLBJD->pLBJDNext = *ppLBJDTou;
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
        int ibStart = 0;
        while (!(ibStart == 1 && tpLBJDNow == *ppLBJDTou)) {
            // 当遍历开始并且又一次回到头指针时，遍历结束
            ibStart = 1;
            if (tpLBJDNow->iShuZhi == iShuZhi) {
                if (tpLBJDNow == *ppLBJDTou) {
                    // 刚好是头
                    *ppLBJDTou = tpLBJDNow->pLBJDNext;
                    free(tpLBJDNow);
                    tpLBJDNow = *ppLBJDTou;
                    // 尾结点指针域也要变
                    (*ppLBJDWei)->pLBJDNext = *ppLBJDTou;
                } else if (tpLBJDNow == *ppLBJDWei) {
                    // 刚好是尾
                    // 把上一个结点的指针域改成头指针
                    tpLBJDLast->pLBJDNext = *ppLBJDTou;
                    *ppLBJDWei = tpLBJDLast;
                    free(tpLBJDNow);
                    // 设置头指针，遍历结束
                    tpLBJDNow = *ppLBJDTou;
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

void yueSeFuWenTi(LBJD **ppLBJDTou, LBJD **ppLBJDWei, int iKill) {
    // 当前结点，上一个结点
    LBJD *tpLBJDNow = *ppLBJDTou, *tpLBJDLast = *ppLBJDTou;

    if (*ppLBJDTou != NULL) {
        printf("kill:");
        int ii = iKill;
        while (ii > 0) {
            for (int ij = 1; ij < iKill; ij++) {
                tpLBJDLast = tpLBJDNow;
                tpLBJDNow = tpLBJDNow->pLBJDNext;
            }
            printf("%d,", tpLBJDNow->iShuZhi);
            if (tpLBJDNow == *ppLBJDTou) {
                // 刚好是头
                *ppLBJDTou = tpLBJDNow->pLBJDNext;
                free(tpLBJDNow);
                tpLBJDNow = *ppLBJDTou;
                // 尾结点指针域也要变
                (*ppLBJDWei)->pLBJDNext = *ppLBJDTou;
            } else if (tpLBJDNow == *ppLBJDWei) {
                // 刚好是尾
                // 把上一个结点的指针域改成头指针
                tpLBJDLast->pLBJDNext = *ppLBJDTou;
                *ppLBJDWei = tpLBJDLast;
                free(tpLBJDNow);
                // 设置头指针，遍历结束
                tpLBJDNow = *ppLBJDTou;
            } else {
                // 连接当前结点的前一个结点和后一个结点
                tpLBJDLast->pLBJDNext = tpLBJDNow->pLBJDNext;
                free(tpLBJDNow);
                tpLBJDNow = tpLBJDLast->pLBJDNext;
            }
            ii--;
        }
        printf("\n");
    }
}