#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*#####邻接矩阵-无向图#####*/

// 顶点数
#define DING_DIAN_SHU 8

// 输出邻接矩阵
extern void juZhenToString(int[DING_DIAN_SHU][DING_DIAN_SHU]);
// 广度优先遍历
extern void guangDuYouXian(int[DING_DIAN_SHU][DING_DIAN_SHU], int, int *);
// 深度优先遍历
extern void shenDuYouXian(int[DING_DIAN_SHU][DING_DIAN_SHU], int, int *);

int main() {
    // 边数
    int iBianShu = 12;
    // 边列表
    int iarr2Bian[][2] = {{0, 1}, {0, 5}, {1, 2}, {1, 6}, {2, 3}, {3, 6}, {3, 7}, {4, 5}, {4, 7}, {5, 1}, {5, 6}, {6, 7}};
    // 邻接矩阵
    int iarr2WuXiangTu[DING_DIAN_SHU][DING_DIAN_SHU] = {0};
    // 顶点访问情况：0=未访问；1=已访问；
    int iarrDingDianFangWen[DING_DIAN_SHU] = {0};

    // 构造无向图邻接矩阵，无向图是对称的
    for (int ii = 0; ii < iBianShu; ii++) {
        iarr2WuXiangTu[iarr2Bian[ii][0]][iarr2Bian[ii][1]] = 1;
        iarr2WuXiangTu[iarr2Bian[ii][1]][iarr2Bian[ii][0]] = 1;
    }

    printf("lin2jie1ju1zhen4:\n");
    juZhenToString(iarr2WuXiangTu);

    printf("guang3du4:");
    guangDuYouXian(iarr2WuXiangTu, DING_DIAN_SHU, iarrDingDianFangWen);
    printf("\n");

    // 重置顶点访问情况
    memset(iarrDingDianFangWen, 0, sizeof(int) * DING_DIAN_SHU);

    printf("shen1du4:");
    shenDuYouXian(iarr2WuXiangTu, DING_DIAN_SHU, iarrDingDianFangWen);
    printf("\n");

    return 0;
}

void juZhenToString(int arr2WuXiangTu[DING_DIAN_SHU][DING_DIAN_SHU]) {
    for (int ii = 0; ii < DING_DIAN_SHU; ii++) {
        for (int ij = 0; ij < DING_DIAN_SHU; ij++) {
            printf("%d,", arr2WuXiangTu[ii][ij]);
        }
        printf("\n");
    }
}

void guangDuYouXian(int arr2WuXiangTu[DING_DIAN_SHU][DING_DIAN_SHU], int iArrLen, int *piarrDingDianFangWen) {
    // 队列，队列头，队列尾
    int iarrDuiLie[100] = {0}, iDuiLieTou = 0, iDuiLieWei = 0;
    // 临时变量
    int tiDingDian = 0;

    // 外层循环保证所有的顶点都会遍历一次
    for (int ii = 0; ii < DING_DIAN_SHU; ii++) {
        iarrDuiLie[iDuiLieWei++] = ii;
        while (iDuiLieTou <= iDuiLieWei) {
            // 出队
            tiDingDian = iarrDuiLie[iDuiLieTou++];
            if (piarrDingDianFangWen[tiDingDian] == 1) {
                // 访问过就跳过
                continue;
            }
            // 访问顶点，并标记
            printf("%d,", tiDingDian);
            piarrDingDianFangWen[tiDingDian] = 1;
            // 遍历这个结点的边
            // 优先遍历一行，把遇到的没访问过的顶点都入队
            for (int ij = 0; ij < DING_DIAN_SHU; ij++) {
                if (arr2WuXiangTu[tiDingDian][ij] == 1 && piarrDingDianFangWen[ij] == 0) {
                    iarrDuiLie[iDuiLieWei++] = ij;
                }
            }
        }
    }
}

void shenDuYouXian(int (*piarrYiHang)[DING_DIAN_SHU], int iArrLen, int *piarrDingDianFangWen) {
    // 栈，栈顶
    int iarrZhan[100] = {0}, iZhanDing = 0;
    // 临时变量
    int tiDingDian = 0;

    // 外层循环保证所有的顶点都会遍历一次
    for (int ii = 0; ii < DING_DIAN_SHU; ii++) {
        iarrZhan[iZhanDing++] = ii;
        while (iZhanDing > 0) {
            // 出栈
            tiDingDian = iarrZhan[--iZhanDing];
            if (piarrDingDianFangWen[tiDingDian] == 1) {
                // 访问过就跳过
                continue;
            }
            // 访问顶点，并标记
            printf("%d,", tiDingDian);
            piarrDingDianFangWen[tiDingDian] = 1;
            // 遍历这个结点的边
            for (int j = 0; j < DING_DIAN_SHU; j++) {
                // 如果找到没有访问过的新顶点，就访问新顶点，等新顶点访问结束后回来继续
                if (piarrYiHang[tiDingDian][j] == 1 && piarrDingDianFangWen[j] == 0) {
                    // 这里先把自己入栈，然后再把要访问的新顶点入栈
                    // 这样就实现了新顶点访问结束后在回来继续访问的逻辑
                    iarrZhan[iZhanDing++] = tiDingDian;
                    iarrZhan[iZhanDing++] = j;
                    break;
                }
            }
        }
    }
}