#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*#####拓扑排序-有向无环图#####*/

// 有向图顶点数
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
// 输出有向图
extern void shuChuYouXiangTu(LJBJD *[DING_DIAN_SHU], int);
// 拓扑排序
extern void tuoPuPaiXu(LJBJD *[DING_DIAN_SHU], int);

/*#####实现代码#####*/

int main() {
    // 边数
    int iBianShu = 12;
    // 边列表
    int iarr2Bian[][2] = {{0, 1}, {0, 5}, {1, 2}, {1, 6}, {2, 3}, {3, 6}, {3, 7}, {4, 5}, {4, 7}, {5, 1}, {5, 6}, {6, 7}};
    // 邻接表
    LJBJD *parrYouXiangTu[DING_DIAN_SHU] = {NULL};

    // 构造有向图邻接表，有向图有方向
    for (int i = 0; i < iBianShu; i++) {
        tianJiaJieDian(parrYouXiangTu, iarr2Bian[i][0], iarr2Bian[i][1]);
    }

    printf("lin2jie1biao3:\n");
    shuChuYouXiangTu(parrYouXiangTu, DING_DIAN_SHU);

    printf("tuo4pu3pai2xu4:\n");
    tuoPuPaiXu(parrYouXiangTu, DING_DIAN_SHU);

    return 0;
}

void tianJiaJieDian(LJBJD *parrYouXiangTu[DING_DIAN_SHU], int iDingDianChu, int iDingDianRu) {
    // 构造邻接表结点
    LJBJD *tpLJBJDNew = NULL, *tpLJBJD = NULL;

    tpLJBJDNew = (LJBJD *)malloc(sizeof(LJBJD));
    tpLJBJDNew->iDingDian = iDingDianRu;
    tpLJBJDNew->pLJBJDNext = NULL;
    // 插入结点到顶点的邻接表的末尾
    if (parrYouXiangTu[iDingDianChu] == NULL) {
        parrYouXiangTu[iDingDianChu] = tpLJBJDNew;
    } else {
        tpLJBJD = parrYouXiangTu[iDingDianChu];
        while (tpLJBJD->pLJBJDNext != NULL) {
            tpLJBJD = tpLJBJD->pLJBJDNext;
        }
        tpLJBJD->pLJBJDNext = tpLJBJDNew;
    }
}

void shuChuYouXiangTu(LJBJD *parrYouXiangTu[DING_DIAN_SHU], int iArrLen) {
    LJBJD *tpLJBJD = NULL;

    for (int i = 0; i < iArrLen; i++) {
        tpLJBJD = parrYouXiangTu[i];
        printf("%d:", i);
        while (tpLJBJD != NULL) {
            printf("%d,", tpLJBJD->iDingDian);
            tpLJBJD = tpLJBJD->pLJBJDNext;
        }
        printf("\n");
    }
}

void tuoPuPaiXu(LJBJD *parrYouXiangTu[DING_DIAN_SHU], int iArrLen) {
    LJBJD *tpLJBJD = NULL;
    // 入度统计
    int iarrRuDuTongJi[DING_DIAN_SHU] = {0};

    // 统计所有顶点的入度
    for (int i = 0; i < iArrLen; i++) {
        tpLJBJD = parrYouXiangTu[i];
        while (tpLJBJD != NULL) {
            iarrRuDuTongJi[tpLJBJD->iDingDian]++;
            tpLJBJD = tpLJBJD->pLJBJDNext;
        }
    }
    // 拓扑排序就是不断地寻找入读为0的顶点
    while (1) {
        int ibDone = 1;
        for (int i = 0; i < iArrLen; i++) {
            if (iarrRuDuTongJi[i] > 0) {
                // 顶点入度不为0，循环继续
                ibDone = 0;
            } else if (iarrRuDuTongJi[i] == 0) {
                // 入度为0的顶点，移除所有从这个顶点出发的弧（弧头顶点入度-1）
                tpLJBJD = parrYouXiangTu[i];
                while (tpLJBJD != NULL) {
                    iarrRuDuTongJi[tpLJBJD->iDingDian]--;
                    tpLJBJD = tpLJBJD->pLJBJDNext;
                }
                printf("%d,", i);
                iarrRuDuTongJi[i] = -1;
            }
        }
        if (ibDone == 1) {
            break;
        }
    }
}