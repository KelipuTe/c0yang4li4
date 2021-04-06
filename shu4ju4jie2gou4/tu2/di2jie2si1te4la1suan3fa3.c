#include <stdio.h>

/*#####无向图-迪杰斯特拉算法#####*/

// 无向图顶点数
#define DING_DIAN_SHU 8
// 临界权重，用于标记
#define LIN_JIE_QUAN_ZHONG 65535

// 输出无向图
extern void shuChuWuXiangTu(int (*)[DING_DIAN_SHU]);
// 输出最短路径
extern void shuChuZuiDuanLuJing(int *, int *);

int main() {
    // 路径列表数量
    int iBianShu = 12;
    // 带权重的路径列表
    int iarr2Bian[][3] = {{0, 1, 10}, {0, 5, 11}, {1, 2, 8}, {1, 6, 16}, {2, 3, 22}, {3, 6, 4}, {3, 7, 6}, {4, 5, 16}, {4, 7, 7}, {5, 1, 13}, {5, 6, 9}, {6, 7, 3}};
    // 邻接矩阵
    int iarr2WuXiangTu[DING_DIAN_SHU][DING_DIAN_SHU] = {0};
    // 记录从顶点0开始到达各个顶点的最短路径的权重(这里假设从顶点0开始)
    int iarrZuiXiaoQuanZhong[DING_DIAN_SHU] = {0};
    // 相关顶点用于记录上面最短路径的来源，即对应的路径是从哪个顶点来的
    int iarrXiangGuanDingDian[DING_DIAN_SHU] = {0};
    // 已经确认的顶点，用于记录已经找到最短路径的顶点，0表示未确认，1表示已确认
    int iarrQueRenDeDingDian[DING_DIAN_SHU] = {0};

    // 初始化邻接矩阵，这里和普通邻接矩阵初始化的方式不一样，除了对角线默认所有的值都是临界权重，对角线默认为0(自己到自己认为权重是0)
    for (int i = 0; i < DING_DIAN_SHU; i++) {
        for (int j = 0; j < DING_DIAN_SHU; j++) {
            if (i == j) {
                iarr2WuXiangTu[i][j] = 0;
            } else {
                iarr2WuXiangTu[i][j] = LIN_JIE_QUAN_ZHONG;
            }
        }
    }
    for (int i = 0; i < iBianShu; i++) {
        iarr2WuXiangTu[iarr2Bian[i][0]][iarr2Bian[i][1]] = iarr2Bian[i][2];
        iarr2WuXiangTu[iarr2Bian[i][1]][iarr2Bian[i][0]] = iarr2Bian[i][2];
    }
    // 默认顶点0到顶点0的路径设置为0，默认顶点0是从顶点0出发的，默认顶点0已确认
    iarrZuiXiaoQuanZhong[0] = 0;
    iarrXiangGuanDingDian[0] = 0;
    iarrQueRenDeDingDian[0] = 1;
    // 初始化相关顶点，因为是从顶点0开始的，所以初始化的时候，最短路径全部默认是从顶点0出发的
    for (int i = 0; i < DING_DIAN_SHU; i++) {
        iarrZuiXiaoQuanZhong[i] = iarr2WuXiangTu[0][i];
        iarrXiangGuanDingDian[i] = 0;
    }
    // 每轮判断找到一个最短路径的顶点
    for (int i = 0; i < DING_DIAN_SHU; i++) {
        // 遍历最小权重数组，权重最小的那个顶点就是本轮能确定最短路径的顶点k
        int k = 0, tiZuiXiaoQuanZhong = LIN_JIE_QUAN_ZHONG;
        for (int j = 0; j < DING_DIAN_SHU; j++) {
            if (iarrQueRenDeDingDian[j] == 0) {
                if (iarrZuiXiaoQuanZhong[j] < tiZuiXiaoQuanZhong) {
                    k = j;
                    tiZuiXiaoQuanZhong = iarrZuiXiaoQuanZhong[j];
                }
            }
        }
        // 标记顶点k为已确认顶点
        iarrQueRenDeDingDian[k] = 1;
        // 从顶点k出发，带上从顶点0到顶点k的路径权重，重新计算从顶点0开始到各个顶点的最短路径权重
        for (int j = 0; j < DING_DIAN_SHU; j++) {
            if (iarrQueRenDeDingDian[j] == 0 && (tiZuiXiaoQuanZhong + iarr2WuXiangTu[k][j] < iarrZuiXiaoQuanZhong[j])) {
                // 如果发现从顶点k出发能找到更短的路径，就更新
                iarrZuiXiaoQuanZhong[j] = tiZuiXiaoQuanZhong + iarr2WuXiangTu[k][j];
                iarrXiangGuanDingDian[j] = k;
            }
        }
    }

    printf("lin2jie1ju1zhen4:\n");
    shuChuWuXiangTu(iarr2WuXiangTu);

    printf("zui4duan3lu4jing4:\n");
    shuChuZuiDuanLuJing(iarrXiangGuanDingDian, iarrZuiXiaoQuanZhong);

    return 0;
}

void shuChuWuXiangTu(int iarr2WuXiangTu[DING_DIAN_SHU][DING_DIAN_SHU]) {
    for (int i = 0; i < DING_DIAN_SHU; i++) {
        for (int j = 0; j < DING_DIAN_SHU; j++) {
            printf("%5d,", iarr2WuXiangTu[i][j]);
        }
        printf("\n");
    }
}

void shuChuZuiDuanLuJing(int *iarrXiangGuanDingDian, int *iarrZuiXiaoQuanZhong) {
    for (int i = 0; i < DING_DIAN_SHU; i++) {
        int j = i;
        printf("quan2zhong4:%3d,lu4jing4:v%d<-", iarrZuiXiaoQuanZhong[i], j);
        // 向上追溯到v0，输出路径
        while (iarrXiangGuanDingDian[j] != 0) {
            j = iarrXiangGuanDingDian[j];
            printf("v%d<-", j);
        }
        printf("v0\n");
    }
}