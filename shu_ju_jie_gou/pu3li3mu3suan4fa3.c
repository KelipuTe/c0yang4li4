#include <stdio.h>

/*#####无向图-普里姆算法#####*/

// 无向图顶点数
#define DING_DIAN_SHU 8
// 临界权重，用于标记
#define LIN_JIE_QUAN_ZHONG 65535

// 无向图邻接矩阵
int iArr2WuXiangTu[DING_DIAN_SHU][DING_DIAN_SHU] = {0};

// 输出无向图
extern void shuChuWuXiangTu();
// 输出最小生成树
void shuChuZuiXiaoShenChengShu(int[][2], int);

/*#####实现代码#####*/

int main()
{
    // 带权重的路径列表
    int iArr2LuJing[][3] = {
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
    // 记录最小生成树的边
    int iArrZuiXiaoShengChengShu[12][2] = {0};
    // 记录最小生成树的顶点到达不在最小生成树中的各个顶点的最小路径权重，如果没有路径到达对应的顶点，就默认设置为临界权重
    int iArrZuiXiaoQuanZhongLieBiao[12] = {0};
    // 相关顶点用于记录上面最小路径权重的来源，即对应的路径是从哪个顶点出来的
    int iArrXiangGuanDingDianLieBiao[12] = {0};

    // 初始化邻接矩阵，这里和普通邻接矩阵初始化的方式不一样
    // 初始化的时候除了对角线默认所有的值都是临界权重，对角线默认为0，自己到自己当然是0
    for (int i = 0; i < DING_DIAN_SHU; i++)
    {
        for (int j = 0; j < DING_DIAN_SHU; j++)
        {
            if (i == j)
            {
                iArr2WuXiangTu[i][j] = 0;
            }
            else
            {
                iArr2WuXiangTu[i][j] = LIN_JIE_QUAN_ZHONG;
            }
        }
    }
    for (int i = 0; i < iLuJingShu; i++)
    {
        int iDingDian1 = iArr2LuJing[i][0];
        int iDingDian2 = iArr2LuJing[i][1];
        iArr2WuXiangTu[iDingDian1][iDingDian2] = iArr2LuJing[i][2];
        iArr2WuXiangTu[iDingDian2][iDingDian1] = iArr2LuJing[i][2];
    }

    // 默认从顶点0开始，已经录入最小生成树的顶点，最小路径权重就标为0，表示顶点已经在最小生成树中
    iArrZuiXiaoQuanZhongLieBiao[0] = 0;
    // 因为是从顶点0开始的，所以默认顶点0是从顶点0出发的
    iArrXiangGuanDingDianLieBiao[0] = 0;
    // 初始化，因为是从顶点0开始的，所以初始化的时候，最小路径全部默认是从顶点0出发的
    for (int i = 0; i < iLuJingShu; i++)
    {
        iArrZuiXiaoQuanZhongLieBiao[i] = iArr2WuXiangTu[0][i];
        iArrXiangGuanDingDianLieBiao[i] = 0;
    }
    // 每轮判断都是寻找从当前已经找到的最小生成树的顶点出发的所有边中最小权重的边和对应的那个顶点
    for (int i = 1, tiNum = 0; i < DING_DIAN_SHU; i++)
    {
        int tiZuiXiaoQuanZhong = LIN_JIE_QUAN_ZHONG;
        int tiDingDian = 0;
        // 比较本次从最小生成树顶点出发的所有边的权重，找出最小的边
        for (int j = 1; j < DING_DIAN_SHU; j++)
        {
            if (iArrZuiXiaoQuanZhongLieBiao[j] != 0 && iArrZuiXiaoQuanZhongLieBiao[j] < tiZuiXiaoQuanZhong)
            {
                tiZuiXiaoQuanZhong = iArrZuiXiaoQuanZhongLieBiao[j];
                tiDingDian = j;
            }
        }
        // 用当前最小权重边的坐标和最小权重边的来源坐标可以表示出一条边
        iArrZuiXiaoShengChengShu[tiNum][0] = tiDingDian;
        iArrZuiXiaoShengChengShu[tiNum][1] = iArrXiangGuanDingDianLieBiao[tiDingDian];
        tiNum++;
        // 把这个顶点标记为已找到
        iArrZuiXiaoQuanZhongLieBiao[tiDingDian] = 0;
        for (int j = 1; j < DING_DIAN_SHU; j++)
        {
            // 把新找到的顶点加入最小生成树，然后把从这个顶点出发的边和当前的最小路劲比较一下，权重更小的路径加入下一轮的判断
            if (iArrZuiXiaoQuanZhongLieBiao[j] != 0 && iArr2WuXiangTu[tiDingDian][j] < iArrZuiXiaoQuanZhongLieBiao[j])
            {
                iArrZuiXiaoQuanZhongLieBiao[j] = iArr2WuXiangTu[tiDingDian][j];
                iArrXiangGuanDingDianLieBiao[j] = tiDingDian;
            }
        }
    }

    printf("wu2xiang4tu2-lin2jie1ju1zhen4:\n");
    shuChuWuXiangTu();

    printf("zui4xiao3sheng1cheng2shu4:\n");
    shuChuZuiXiaoShenChengShu(iArrZuiXiaoShengChengShu, iLuJingShu);

    return 0;
}

void shuChuWuXiangTu()
{
    for (int i = 0; i < DING_DIAN_SHU; i++)
    {
        for (int j = 0; j < DING_DIAN_SHU; j++)
        {
            printf("%5d,", iArr2WuXiangTu[i][j]);
        }
        printf("\n");
    }
}

void shuChuZuiXiaoShenChengShu(int iArrZuiXiaoShengChengShu[][2], int iLuJingShu)
{
    for (int i = 0; i < iLuJingShu; i++)
    {
        if (iArrZuiXiaoShengChengShu[i][0] != 0 || iArrZuiXiaoShengChengShu[i][1] != 0)
        {
            printf("%d,%d\n", iArrZuiXiaoShengChengShu[i][0], iArrZuiXiaoShengChengShu[i][1]);
        }
    }
}