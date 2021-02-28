#include <stdio.h>

/*#####无向图-克鲁斯卡尔算法#####*/

// 输出最小生成树
void shuChuZuiXiaoShenChengShu(int[][2], int);
// 查找顶点来源
int chaZhaoLaiYuan(int[], int);

/*#####实现代码#####*/

int main() {
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
    // 记录顶点来源，用于判断顶点是不是已经在生成树上了
    int iArrDingDianLaiYuanBiao[12] = {0};

    // 克鲁斯卡尔算法不需要把邻接矩阵构造出来
    // 对路径列表按照权重升序排序
    for (int i = 0; i < iLuJingShu; i++) {
        int minIndex = i;
        for (int j = i; j < iLuJingShu; j++) {
            if (iArr2LuJing[j][2] < iArr2LuJing[minIndex][2]) {
                minIndex = j;
            }
        }
        int tiNum1 = iArr2LuJing[i][0];
        int tiNum2 = iArr2LuJing[i][1];
        int tiNum3 = iArr2LuJing[i][2];
        iArr2LuJing[i][0] = iArr2LuJing[minIndex][0];
        iArr2LuJing[i][1] = iArr2LuJing[minIndex][1];
        iArr2LuJing[i][2] = iArr2LuJing[minIndex][2];
        iArr2LuJing[minIndex][0] = tiNum1;
        iArr2LuJing[minIndex][1] = tiNum2;
        iArr2LuJing[minIndex][2] = tiNum3;
    }
    // 依次遍历排序后的路径列表
    for (int i = 0, tiNum = 0; i < iLuJingShu; i++) {
        // 追溯路径的两个顶点
        int tiLaiYuan1 = chaZhaoLaiYuan(iArrDingDianLaiYuanBiao, iArr2LuJing[i][0]);
        int tiLaiYuan2 = chaZhaoLaiYuan(iArrDingDianLaiYuanBiao, iArr2LuJing[i][1]);
        if (tiLaiYuan1 != tiLaiYuan2) {
            // 如果追溯不到同一个顶点，那么这条路径就需要记录下来
            // 无向图不需要处理方向问题，这里任选一个顶点当来源
            iArrDingDianLaiYuanBiao[tiLaiYuan1] = tiLaiYuan2;
            iArrZuiXiaoShengChengShu[tiNum][0] = iArr2LuJing[i][0];
            iArrZuiXiaoShengChengShu[tiNum][1] = iArr2LuJing[i][1];
            tiNum++;
        }
    }

    printf("zui4xiao3sheng1cheng2shu4:\n");
    shuChuZuiXiaoShenChengShu(iArrZuiXiaoShengChengShu, iLuJingShu);

    return 0;
}

void shuChuZuiXiaoShenChengShu(int iArrZuiXiaoShengChengShu[][2], int iLuJingShu) {
    for (int i = 0; i < iLuJingShu; i++) {
        if (iArrZuiXiaoShengChengShu[i][0] != 0 || iArrZuiXiaoShengChengShu[i][1] != 0) {
            printf("%d,%d\n", iArrZuiXiaoShengChengShu[i][0], iArrZuiXiaoShengChengShu[i][1]);
        }
    }
}

int chaZhaoLaiYuan(int iArrDingDianLaiYuanBiao[], int iDingDian) {
    while (iArrDingDianLaiYuanBiao[iDingDian] != 0) {
        // 向上追溯来源顶点
        iDingDian = iArrDingDianLaiYuanBiao[iDingDian];
    }
    return iDingDian;
}