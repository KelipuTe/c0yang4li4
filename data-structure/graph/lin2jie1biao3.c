#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*#####邻接表-无向图#####*/

// 无向图顶点数
#define DING_DIAN_SHU 8

// 邻接表结点
typedef struct LingJieBiaoJieDian {
    // 顶点
    int iDingDian;
    // 下一个结点的指针
    struct LingJieBiaoJieDian *pLJBJDNext;
} LJBJD;

// 添加邻接表结点
extern void tianJiaJieDian(LJBJD *[DING_DIAN_SHU], int, int);
// 输出邻接表
extern void biaoToString(LJBJD *[DING_DIAN_SHU], int);
// 广度优先遍历
extern void guangDuYouXian(LJBJD *[DING_DIAN_SHU], int, int *);
// 深度优先遍历
extern void shenDuYouXian(LJBJD *[DING_DIAN_SHU], int, int *);

int main() {
    // 边数
    int iBianShu = 12;
    // 边列表
    int iarr2Bian[][2] = {{0, 1}, {0, 5}, {1, 2}, {1, 6}, {2, 3}, {3, 6}, {3, 7}, {4, 5}, {4, 7}, {5, 1}, {5, 6}, {6, 7}};
    // 邻接表
    LJBJD *parrWuXiangTu[DING_DIAN_SHU] = {NULL};
    // 顶点访问情况：0=未访问；1=已访问；
    int iarrDingDianFangWen[DING_DIAN_SHU] = {0};

    // 构造无向图邻接表，无向图是对称的
    for (int ii = 0; ii < iBianShu; ii++) {
        tianJiaJieDian(parrWuXiangTu, iarr2Bian[ii][0], iarr2Bian[ii][1]);
        tianJiaJieDian(parrWuXiangTu, iarr2Bian[ii][1], iarr2Bian[ii][0]);
    }

    printf("lin2jie1biao3:\n");
    biaoToString(parrWuXiangTu, DING_DIAN_SHU);

    printf("guang3du4:");
    guangDuYouXian(parrWuXiangTu, DING_DIAN_SHU, iarrDingDianFangWen);
    printf("\n");

    memset(iarrDingDianFangWen, 0, sizeof(int) * DING_DIAN_SHU);

    printf("shen1du4:");
    shenDuYouXian(parrWuXiangTu, DING_DIAN_SHU, iarrDingDianFangWen);
    printf("\n");

    return 0;
}

void tianJiaJieDian(LJBJD *parrWuXiangTu[DING_DIAN_SHU], int iDingDian1, int iDingDian2) {
    // 邻接表新结点，临时变量
    LJBJD *tpLJBJDNew = NULL, *tpLJBJD = NULL;

    tpLJBJDNew = (LJBJD *)malloc(sizeof(LJBJD));
    tpLJBJDNew->iDingDian = iDingDian2;
    tpLJBJDNew->pLJBJDNext = NULL;
    // 插入节点到顶点邻接表的末尾
    if (parrWuXiangTu[iDingDian1] == NULL) {
        parrWuXiangTu[iDingDian1] = tpLJBJDNew;
    } else {
        tpLJBJD = parrWuXiangTu[iDingDian1];
        while (tpLJBJD->pLJBJDNext != NULL) {
            tpLJBJD = tpLJBJD->pLJBJDNext;
        }
        tpLJBJD->pLJBJDNext = tpLJBJDNew;
    }
}

void biaoToString(LJBJD *parrWuXiangTu[DING_DIAN_SHU], int iArrLen) {
    LJBJD *tpLJBJD = NULL;

    for (int i = 0; i < iArrLen; i++) {
        tpLJBJD = parrWuXiangTu[i];
        printf("%d:", i);
        while (tpLJBJD != NULL) {
            printf("%d,", tpLJBJD->iDingDian);
            tpLJBJD = tpLJBJD->pLJBJDNext;
        }
        printf("\n");
    }
}

void guangDuYouXian(LJBJD *parrWuXiangTu[DING_DIAN_SHU], int iArrLen, int *piarrDingDianFangWen) {
    // 队列，队列头，队列尾
    int iarrDuiLie[100] = {0}, iDuiLieTou = 0, iDuiLieWei = 0;
    // 临时变量
    int tiDingDian = 0;
    LJBJD *tpLJBJD = NULL;

    for (int i = 0; i < iArrLen; i++) {
        iarrDuiLie[iDuiLieWei++] = i;
        while (iDuiLieTou <= iDuiLieWei) {
            tiDingDian = iarrDuiLie[iDuiLieTou++];
            if (piarrDingDianFangWen[tiDingDian] == 1) {
                continue;
            }
            printf("%d,", tiDingDian);
            piarrDingDianFangWen[tiDingDian] = 1;
            tpLJBJD = parrWuXiangTu[tiDingDian];
            while (tpLJBJD != NULL) {
                tiDingDian = tpLJBJD->iDingDian;
                if (piarrDingDianFangWen[tiDingDian] == 0) {
                    iarrDuiLie[iDuiLieWei++] = tiDingDian;
                }
                tpLJBJD = tpLJBJD->pLJBJDNext;
            }
        }
    }
}

void shenDuYouXian(LJBJD *parrWuXiangTu[DING_DIAN_SHU], int iArrLen, int *piarrDingDianFangWen) {
    // 栈，栈顶
    int iarrZhan[100] = {0}, iZhanDing = 0;
    // 临时变量
    int tiDingDian = 0, tiDingDianLast = 0;
    LJBJD *tpLJBJD = NULL;

    for (int i = 0; i < DING_DIAN_SHU; i++) {
        iarrZhan[iZhanDing++] = i;
        while (iZhanDing > 0) {
            tiDingDian = iarrZhan[--iZhanDing];
            if (piarrDingDianFangWen[tiDingDian] == 1) {
                continue;
            }
            printf("%d,", tiDingDian);
            piarrDingDianFangWen[tiDingDian] = 1;
            tiDingDianLast = tiDingDian;
            tpLJBJD = parrWuXiangTu[tiDingDian];
            while (tpLJBJD != NULL) {
                tiDingDian = tpLJBJD->iDingDian;
                if (piarrDingDianFangWen[tiDingDian] == 0) {
                    iarrZhan[iZhanDing++] = tiDingDianLast;
                    iarrZhan[iZhanDing++] = tiDingDian;
                    break;
                }
                tpLJBJD = tpLJBJD->pLJBJDNext;
            }
        }
    }
}