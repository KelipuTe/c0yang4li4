#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*#####无向图-邻接矩阵#####*/

// 无向图顶点数
#define DING_DIAN_SHU 8

// 输出无向图
extern void shuChuWuXiangTu(int (*)[DING_DIAN_SHU], int);
// 广度优先遍历
extern void guangDuYouXianBianLi(int (*)[DING_DIAN_SHU], int, int *);
// 深度优先遍历
extern void shenDuYouXianBianLi(int (*)[DING_DIAN_SHU], int, int *);

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
    // 无向图邻接矩阵
    int iarr2WuXiangTu[DING_DIAN_SHU][DING_DIAN_SHU] = {0};
    // 顶点访问情况：0=未访问；1=已访问；
    int iarrDingDianFangWen[DING_DIAN_SHU] = {0};

    // 构造无向图邻接矩阵
    for (int i = 0; i < iLuJingShu; i++) {
        // 无向图是对称的
        iarr2WuXiangTu[iarr2LuJing[i][0]][iarr2LuJing[i][1]] = 1;
        iarr2WuXiangTu[iarr2LuJing[i][1]][iarr2LuJing[i][0]] = 1;
    }

    printf("wu2xiang4tu2-lin2jie1ju1zhen4:\n");
    shuChuWuXiangTu(iarr2WuXiangTu, DING_DIAN_SHU);

    printf("guang3du4you1xian1bian4li4:");
    guangDuYouXianBianLi(iarr2WuXiangTu, DING_DIAN_SHU, iarrDingDianFangWen);
    printf("\n");

    // 重置顶点访问情况
    memset(iarrDingDianFangWen, 0, sizeof(int) * DING_DIAN_SHU);

    printf("shen1du4you1xian1bian4li4:");
    shenDuYouXianBianLi(iarr2WuXiangTu, DING_DIAN_SHU, iarrDingDianFangWen);
    printf("\n");

    return 0;
}

void shuChuWuXiangTu(int (*piarrYiHang)[DING_DIAN_SHU], int iArrLieShu) {
    for (int i = 0; i < iArrLieShu; i++) {
        for (int j = 0; j < DING_DIAN_SHU; j++) {
            printf("%d,", piarrYiHang[i][j]);
        }
        printf("\n");
    }
}

void guangDuYouXianBianLi(int (*piarrYiHang)[DING_DIAN_SHU], int iArrLieShu, int *piarrDingDianFangWen) {
    // 广度优先遍历需要用到队列
    int iarrDuiLie[100] = {0};
    int iDuiLieTou = 0, iDuiLieWei = 0;
    int tiDingDian = 0;

    // 外层循环保证所有的顶点都会遍历一次
    for (int i = 0; i < DING_DIAN_SHU; i++) {
        iarrDuiLie[iDuiLieWei++] = i;
        while (iDuiLieTou <= iDuiLieWei) {
            tiDingDian = iarrDuiLie[iDuiLieTou++];
            if (piarrDingDianFangWen[tiDingDian] == 1) {
                continue;
            }
            // 输出访问到的顶点
            printf("%d,", tiDingDian);
            // 记录顶点访问情况
            piarrDingDianFangWen[tiDingDian] = 1;
            for (int j = 0; j < DING_DIAN_SHU; j++) {
                // 优先遍历一行，把遇到的顶点都入队
                if (piarrYiHang[tiDingDian][j] == 1 && piarrDingDianFangWen[j] == 0) {
                    iarrDuiLie[iDuiLieWei++] = j;
                }
            }
        }
    }
}

void shenDuYouXianBianLi(int (*piarrYiHang)[DING_DIAN_SHU], int iArrLieShu, int *piarrDingDianFangWen) {
    // 深度优先遍历需要用到栈或者递归
    int iarrZhan[100] = {0};
    int iZhanDing = 0;
    int tiDingDian = 0;

    // 外层循环保证所有的顶点都会遍历一次
    for (int i = 0; i < DING_DIAN_SHU; i++) {
        iarrZhan[iZhanDing++] = i;
        while (iZhanDing > 0) {
            tiDingDian = iarrZhan[--iZhanDing];
            if (piarrDingDianFangWen[tiDingDian] == 1) {
                continue;
            }
            // 输出访问到的顶点
            printf("%d,", tiDingDian);
            // 记录顶点访问情况
            piarrDingDianFangWen[tiDingDian] = 1;
            for (int j = 0; j < DING_DIAN_SHU; j++) {
                if (piarrYiHang[tiDingDian][j] == 1 && piarrDingDianFangWen[j] == 0) {
                    // 如果找到没有访问过的顶点，就访问该顶点，然后结束本顶点的遍历
                    // 注意先把自己入栈，然后再把要访问的顶点入栈
                    iarrZhan[iZhanDing++] = tiDingDian;
                    iarrZhan[iZhanDing++] = j;
                    break;
                }
            }
        }
    }
}