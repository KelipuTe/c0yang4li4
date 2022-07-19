#include <stdio.h>

/*#####无向图-弗洛伊德算法#####*/

// 无向图顶点数
#define DING_DIAN_SHU 8
// 临界权重，用于标记
#define LIN_JIE_QUAN_ZHONG 65535

// 输出无向图
extern void shuChuWuXiangTu(int (*)[DING_DIAN_SHU], int);
// 输出最短路径
void shuChuZuoDuanLuJing(int *, int *, int);

/*#####实现代码#####*/

int main() {
    // 带权重的路径列表
    int iarr2LuJing[][3] = {
        {0, 1, 10},
        {0, 5, 11},
        {1, 2, 8},
        {1, 6, 16},
        {2, 3, 22},
        {3, 6, 4},
        {3, 7, 6},
        {4, 5, 16},
        {4, 7, 7},
        {5, 1, 13},
        {5, 6, 9},
        {6, 7, 3},
    };
    // 路径列表数量
    int iLuJingShu = 12;
    // 无向图邻接矩阵
    int iarr2WuXiangTu[DING_DIAN_SHU][DING_DIAN_SHU] = {0};
    // 最短路径来源，[i][j]=k，就表示顶点i到顶点j需要经过顶点k
    int iarr2ZuiDuanLuJing[DING_DIAN_SHU][DING_DIAN_SHU] = {0};
    // 初始化邻接矩阵，这里和普通邻接矩阵初始化的方式不一样
    // 初始化的时候除了对角线默认所有的值都是临界权重，对角线默认为0，自己到自己认为权重是0
    for (int i = 0; i < DING_DIAN_SHU; i++) {
        for (int j = 0; j < DING_DIAN_SHU; j++) {
            if (i == j) {
                iarr2WuXiangTu[i][j] = 0;
            } else {
                iarr2WuXiangTu[i][j] = LIN_JIE_QUAN_ZHONG;
            }
        }
    }
    for (int i = 0; i < iLuJingShu; i++) {
        iarr2WuXiangTu[iarr2LuJing[i][0]][iarr2LuJing[i][1]] = iarr2LuJing[i][2];
        iarr2WuXiangTu[iarr2LuJing[i][1]][iarr2LuJing[i][0]] = iarr2LuJing[i][2];
    }
    // 初始化最短路径来源
    for (int i = 0; i < DING_DIAN_SHU; i++) {
        for (int j = 0; j < DING_DIAN_SHU; j++) {
            iarr2ZuiDuanLuJing[i][j] = i;
        }
    }
    // 依次以顶点k为中转点
    for (int k = 0; k < DING_DIAN_SHU; k++) {
        // 依次选两个顶点顶点i和顶点j
        for (int i = 0; i < DING_DIAN_SHU; i++) {
            for (int j = 0; j < DING_DIAN_SHU; j++) {
                // 比较（i,j）和（i,k）+(k,j)的大小
                if (iarr2WuXiangTu[i][j] > iarr2WuXiangTu[i][k] + iarr2WuXiangTu[k][j]) {
                    iarr2WuXiangTu[i][j] = iarr2WuXiangTu[i][k] + iarr2WuXiangTu[k][j];
                    iarr2ZuiDuanLuJing[i][j] = k;
                }
            }
        }
    }

    printf("wu2xiang4tu2-lin2jie1ju1zhen4:\n");
    shuChuWuXiangTu(iarr2WuXiangTu, DING_DIAN_SHU);

    printf("ju4jing4lai2yuan2:\n");
    shuChuWuXiangTu(iarr2ZuiDuanLuJing, DING_DIAN_SHU);

    return 0;
}

void shuChuWuXiangTu(int (*piarrYiHang)[DING_DIAN_SHU], int iArrLen) {
    for (int i = 0; i < iArrLen; i++) {
        for (int j = 0; j < DING_DIAN_SHU; j++) {
            printf("%5d,", piarrYiHang[i][j]);
        }
        printf("\n");
    }
}