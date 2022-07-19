#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*#####有向无环图-拓扑排序#####*/

// 有向图顶点数
#define DING_DIAN_SHU 9

// 邻接表结点
typedef struct LingJieBiaoJieDian {
    // 顶点
    int iDingDian;
    // 路径权重
    int iQuanZhong;
    // 下一个结点的指针
    struct LingJieBiaoJieDian *pLJBJDNext;
} LJBJD;

// 添加邻接表结点
extern void tianJiaJieDian(LJBJD *[DING_DIAN_SHU], int, int, int);
// 输出有向图
extern void shuChuYouXiangTu(LJBJD *[DING_DIAN_SHU], int);
// 输出数组
extern void shuChuShuZu();

/*#####实现代码#####*/

int main() {
    // 路径列表
    int iarr2LuJing[][3] = {
        {0, 1, 6},
        {0, 2, 4},
        {0, 3, 5},
        {1, 4, 1},
        {2, 4, 1},
        {3, 5, 2},
        {4, 6, 9},
        {4, 7, 7},
        {5, 7, 4},
        {6, 8, 2},
        {7, 8, 4}};
    // 路径列表数量
    int iLuJingShu = 11;
    // 有向图邻接表，下标是弧尾
    LJBJD *parrWuXiangTuChu[DING_DIAN_SHU] = {NULL};
    // 有向图邻接表，下标是弧头
    LJBJD *parrWuXiangTuRu[DING_DIAN_SHU] = {NULL};

    // 构造有向图邻接矩阵
    for (int i = 0; i < iLuJingShu; i++) {
        tianJiaJieDian(parrWuXiangTuChu, iarr2LuJing[i][0], iarr2LuJing[i][1], iarr2LuJing[i][2]);
        tianJiaJieDian(parrWuXiangTuRu, iarr2LuJing[i][1], iarr2LuJing[i][0], iarr2LuJing[i][2]);
    }

    printf("wu2xiang4tu2-lin2jie1biao3:\n");
    shuChuWuXiangTu(parrWuXiangTuChu, DING_DIAN_SHU);

    printf("wu2xiang4tu2-lin2jie1biao3:\n");
    shuChuWuXiangTu(parrWuXiangTuRu, DING_DIAN_SHU);

    // 最早开始时间
    int iarrZuiZaoKaiShi[DING_DIAN_SHU] = {0};
    // 最晚开始时间
    int iarrZuiWanKaiShi[DING_DIAN_SHU] = {0};
    LJBJD *tpLJBJD = NULL;
    // 入度统计
    int iarrRuDuTongJi[DING_DIAN_SHU] = {0};
    // 出度统计
    int iarrChuDuTongJi[DING_DIAN_SHU] = {0};
    int iArrLen = DING_DIAN_SHU;
    // 最长路径权重
    int iZuiChangLuJing = 0;

    // 算最早开始时间
    // 用拓扑排序的思路，算一下从起始顶点到各个顶点的最长路径权重（就等于最早开始时间）
    for (int i = 0; i < iArrLen; i++) {
        tpLJBJD = parrWuXiangTuChu[i];
        while (tpLJBJD != NULL) {
            iarrRuDuTongJi[tpLJBJD->iDingDian]++;
            tpLJBJD = tpLJBJD->pLJBJDNext;
        }
    }
    while (1) {
        int ibDone = 1;
        for (int i = 0; i < iArrLen; i++) {
            if (iarrRuDuTongJi[i] > 0) {
                ibDone = 0;
            } else if (iarrRuDuTongJi[i] == 0) {
                tpLJBJD = parrWuXiangTuChu[i];
                while (tpLJBJD != NULL) {
                    // 依次计算顶点的最长路径权重
                    if (iarrZuiZaoKaiShi[tpLJBJD->iDingDian] < iarrZuiZaoKaiShi[i] + tpLJBJD->iQuanZhong) {
                        iarrZuiZaoKaiShi[tpLJBJD->iDingDian] = iarrZuiZaoKaiShi[i] + tpLJBJD->iQuanZhong;
                    }
                    // 保存最长路径权重
                    if (iZuiChangLuJing < iarrZuiZaoKaiShi[tpLJBJD->iDingDian]) {
                        iZuiChangLuJing = iarrZuiZaoKaiShi[tpLJBJD->iDingDian];
                    }
                    iarrRuDuTongJi[tpLJBJD->iDingDian]--;
                    tpLJBJD = tpLJBJD->pLJBJDNext;
                }
                iarrRuDuTongJi[i] = -1;
            }
        }
        if (ibDone == 1) {
            break;
        }
    }

    printf("zui4zao3kai1shi3:\n");
    shuChuShuZu(iarrZuiZaoKaiShi, DING_DIAN_SHU);

    for (int i = 0; i < iArrLen; i++) {
        iarrZuiWanKaiShi[i] = iZuiChangLuJing;
    }
    // 算最晚开始时间
    // 反过来用拓扑排序的思路，计算最晚开始时间
    for (int i = 0; i < iArrLen; i++) {
        tpLJBJD = parrWuXiangTuRu[i];
        while (tpLJBJD != NULL) {
            iarrChuDuTongJi[tpLJBJD->iDingDian]++;
            tpLJBJD = tpLJBJD->pLJBJDNext;
        }
    }
    while (1) {
        int ibDone = 1;
        for (int i = 0; i < iArrLen; i++) {
            if (iarrChuDuTongJi[i] > 0) {
                ibDone = 0;
            } else if (iarrChuDuTongJi[i] == 0) {
                tpLJBJD = parrWuXiangTuRu[i];
                while (tpLJBJD != NULL) {
                    if (iarrZuiWanKaiShi[tpLJBJD->iDingDian] > iarrZuiWanKaiShi[i] - tpLJBJD->iQuanZhong) {
                        iarrZuiWanKaiShi[tpLJBJD->iDingDian] = iarrZuiWanKaiShi[i] - tpLJBJD->iQuanZhong;
                    }
                    iarrChuDuTongJi[tpLJBJD->iDingDian]--;
                    tpLJBJD = tpLJBJD->pLJBJDNext;
                }
                iarrChuDuTongJi[i] = -1;
            }
        }
        if (ibDone == 1) {
            break;
        }
    }

    printf("zui4wan3kai1shi3:\n");
    shuChuShuZu(iarrZuiWanKaiShi, DING_DIAN_SHU);

    int iarrHuoDongZuiZaoKaiShi[11] = {0};
    // 活动的最早开始时间就是弧尾顶点的最早开始时间，到了这个顶点才可以开始任务
    for (int i = 0; i < iLuJingShu; i++) {
        iarrHuoDongZuiZaoKaiShi[i] = iarrZuiZaoKaiShi[iarr2LuJing[i][0]];
    }
    printf("huo2dong4zui4zao3kai1shi1:\n");
    shuChuShuZu(iarrHuoDongZuiZaoKaiShi, iLuJingShu);

    int iarrHuoDongZuiWanKaiShi[11] = {0};
    // 活动的最晚开始时间就是弧头顶点的最晚开始时间减去路径权重，经过路径权重的时间到弧头顶点刚好是弧头顶点的最晚开始时间
    for (int i = 0; i < iLuJingShu; i++) {
        iarrHuoDongZuiWanKaiShi[i] = iarrZuiWanKaiShi[iarr2LuJing[i][1]] - iarr2LuJing[i][2];
    }
    printf("huo2dong4zui4wan3kai1shi1:\n");
    shuChuShuZu(iarrHuoDongZuiWanKaiShi, iLuJingShu);

    // 如果活动最早开始时间等于最晚开始时间，那这个路径就是关键路径，涉及到的顶点就是关键路径顶点

    return 0;
}

void tianJiaJieDian(LJBJD *parrWuXiangTu[DING_DIAN_SHU], int iDingDian1, int iDingDian2, int iQuanZhong) {
    // 构造邻接表结点
    LJBJD *tpLJBJDNew = (LJBJD *)malloc(sizeof(LJBJD));
    LJBJD *tpLJBJD = NULL;

    tpLJBJDNew->iDingDian = iDingDian2;
    tpLJBJDNew->iQuanZhong = iQuanZhong;
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

void shuChuWuXiangTu(LJBJD *parrWuXiangTu[DING_DIAN_SHU], int iArrLen) {
    LJBJD *tpLJBJD = NULL;

    for (int i = 0; i < iArrLen; i++) {
        tpLJBJD = parrWuXiangTu[i];
        printf("%d:", i);
        while (tpLJBJD != NULL) {
            printf("%dq%d,", tpLJBJD->iDingDian, tpLJBJD->iQuanZhong);
            tpLJBJD = tpLJBJD->pLJBJDNext;
        }
        printf("\n");
    }
    printf("\n");
}

void shuChuShuZu(int *parrShuZu, int iArrLen) {
    for (int i = 0; i < iArrLen; i++) {
        printf("%d-%d,", i, parrShuZu[i]);
    }
    printf("\n");
}