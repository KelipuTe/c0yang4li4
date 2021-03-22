#include <math.h>
#include <stdio.h>

/*#####回溯-八皇后#####*/

// 棋盘8*8
#define HUANG_HOU_SHU 8

// 输出符合条件的位置
extern void shuChuWeiZhi(int[HUANG_HOU_SHU]);
// 主体递归
extern void baHuangHou(int *, int[HUANG_HOU_SHU], int);
// 校验皇后位置
extern int jiaoYan(int[HUANG_HOU_SHU], int, int);

int main() {
    // 每一排皇后的坐标
    int iarrHuangHou[HUANG_HOU_SHU] = {0};
    // 输出符合条件的位置总数
    int iCount = 0;

    baHuangHou(&iCount, iarrHuangHou, 0);
    printf("total:%d\n", iCount);

    return 0;
}

void shuChuWeiZhi(int iarrHuangHou[HUANG_HOU_SHU]) {
    printf("get\n");
    for (int ii = 0; ii < HUANG_HOU_SHU; ii++) {
        for (int ij = 0; ij < HUANG_HOU_SHU; ij++) {
            if (ij != iarrHuangHou[ii]) {
                printf("0,");
            } else {
                printf("1,");
            }
        }
        printf("\n");
    }
    printf("\n");
}

void baHuangHou(int *piCount, int iarrHuangHou[HUANG_HOU_SHU], int iLine) {
    for (int ii = 0; ii < HUANG_HOU_SHU; ii++) {
        // 校验[iLine,ii]位置能不能放
        int iCheckRes = jiaoYan(iarrHuangHou, iLine, ii);
        if (iCheckRes == 1) {
            iarrHuangHou[iLine] = ii;
            if (iLine == HUANG_HOU_SHU - 1) {
                // 已经到最后一行，则找到一个符合条件的解
                shuChuWeiZhi(iarrHuangHou);
                (*piCount)++;
                // 把这行重置，回到上一行继续求解
                iarrHuangHou[iLine] = 0;

                return;
            }
            // 如果没到最后一行，就进入下一行去求解
            baHuangHou(piCount, iarrHuangHou, iLine + 1);
            // 无论下一行有没有解，这行得到求解结束，把这行重置
            // 继续求解这行的下一个位置，或者循环结束回到上一行继续求解
            iarrHuangHou[iLine] = 0;
        }
    }
}

int jiaoYan(int iarrHuangHou[HUANG_HOU_SHU], int iSelfX, int iSelfY) {
    // 自身皇后位置[iSelfX,iSelfY]，前排各个皇后位置[tiX,tiY]
    int tiX = 0, tiY = 0;
    for (int ii = 0; ii < iSelfX; ii++) {
        tiX = ii;
        tiY = iarrHuangHou[ii];
        if (tiY == iSelfY) {
            // 同一列，纵坐标相等
            return 0;
        }
        if (abs(tiX - iSelfX) == abs(tiY - iSelfY)) {
            // 同一斜线，横纵坐标差值的绝对值相等
            return 0;
        }
    }
    return 1;
}
