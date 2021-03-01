#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*#####无向图-邻接表#####*/

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
// 输出无向图
extern void shuChuWuXiangTu(LJBJD *[DING_DIAN_SHU], int);
// 广度优先遍历
extern void guangDuYouXianBianLi(LJBJD *[DING_DIAN_SHU], int, int *);
// 深度优先遍历
extern void shenDuYouXianBianLi(LJBJD *[DING_DIAN_SHU], int, int *);

/*#####实现代码#####*/

int main() {
    // 路径列表
    int iarr2LuJing[][2] = {
        {0, 1},
        {0, 5},
        {1, 2},
        {1, 6},
        {2, 3},
        {3, 6},
        {3, 7},
        {4, 5},
        {4, 7},
        {5, 1},
        {5, 6},
        {6, 7},
    };
    // 路径列表数量
    int iLuJingShu = 12;
    // 无向图邻接表
    LJBJD *parrWuXiangTu[DING_DIAN_SHU] = {NULL};
    // 顶点访问情况：0=未访问；1=已访问；
    int iarrDingDianFangWen[DING_DIAN_SHU] = {0};

    // 构造无向图邻接矩阵
    for (int i = 0; i < iLuJingShu; i++) {
        // 无向图是对称的
        tianJiaJieDian(parrWuXiangTu, iarr2LuJing[i][0], iarr2LuJing[i][1]);
        tianJiaJieDian(parrWuXiangTu, iarr2LuJing[i][1], iarr2LuJing[i][0]);
    }

    printf("wu2xiang4tu2-lin2jie1biao3:\n");
    shuChuWuXiangTu(parrWuXiangTu, DING_DIAN_SHU);

    printf("guang3du4you1xian1bian4li4:");
    guangDuYouXianBianLi(parrWuXiangTu, DING_DIAN_SHU, iarrDingDianFangWen);
    printf("\n");

    memset(iarrDingDianFangWen, 0, sizeof(int) * DING_DIAN_SHU);

    printf("shen1du4you1xian1bian4li4:");
    shenDuYouXianBianLi(parrWuXiangTu, DING_DIAN_SHU, iarrDingDianFangWen);
    printf("\n");

    return 0;
}

void tianJiaJieDian(LJBJD *parrWuXiangTu[DING_DIAN_SHU], int iDingDian1, int iDingDian2) {
    // 构造邻接表结点
    LJBJD *tpLJBJDNew = (LJBJD *)malloc(sizeof(LJBJD));
    LJBJD *tpLJBJD = NULL;

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

void shuChuWuXiangTu(LJBJD *parrWuXiangTu[DING_DIAN_SHU], int iArrLieShu) {
    LJBJD *tpLJBJD = NULL;

    for (int i; i < iArrLieShu; i++) {
        tpLJBJD = parrWuXiangTu[i];
        printf("%d:", i);
        while (tpLJBJD != NULL) {
            printf("%d,", tpLJBJD->iDingDian);
            tpLJBJD = tpLJBJD->pLJBJDNext;
        }
        printf("\n");
    }
}

void guangDuYouXianBianLi(LJBJD *parrWuXiangTu[DING_DIAN_SHU], int iArrLieShu, int *piarrDingDianFangWen) {
    // 广度优先遍历需要用到队列
    int iarrDuiLie[100] = {0};
    int iDuiLieTou = 0, iDuiLieWei = 0;
    int tiDingDian = 0;
    LJBJD *tpLJBJD = NULL;

    for (int i = 0; i < iArrLieShu; i++) {
        iarrDuiLie[iDuiLieWei++] = i;
        while (iDuiLieTou <= iDuiLieWei) {
            tiDingDian = iarrDuiLie[iDuiLieTou++];
            if (piarrDingDianFangWen[tiDingDian] == 1) {
                continue;
            }
            printf("%d,", tiDingDian);
            tpLJBJD = parrWuXiangTu[tiDingDian];
            piarrDingDianFangWen[tiDingDian] = 1;
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

void shenDuYouXianBianLi(LJBJD *parrWuXiangTu[DING_DIAN_SHU], int iArrLieShu, int *piarrDingDianFangWen) {
    int iarrZhan[100] = {0};
    int iZhanDing = 0;
    int tiDingDian = 0, tiDingDianLast = 0;
    LJBJD *tpLJBJD = NULL;

    // 外层循环保证所有的顶点都会遍历一次
    for (int i = 0; i < DING_DIAN_SHU; i++) {
        iarrZhan[iZhanDing++] = i;
        while (iZhanDing > 0) {
            tiDingDian = iarrZhan[--iZhanDing];
            if (piarrDingDianFangWen[tiDingDian] == 1) {
                continue;
            }
            printf("%d,", tiDingDian);
            tpLJBJD = parrWuXiangTu[tiDingDian];
            tiDingDianLast = tiDingDian;
            piarrDingDianFangWen[tiDingDian] = 1;
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