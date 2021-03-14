#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*#####堆排序#####*/

void arrToString(int *iarr, int iArrLen) {
    for (int ii = 0; ii < iArrLen; ii++) {
        printf("%d,", iarr[ii]);
    }
    printf("\n");
}

int main() {
    // int iarr[10] = {99,92,97,86,42,73,3,6,20,34};
    int iarr[10] = {0};
    int iArrLen = 10;

    srand(time(NULL));
    for (int ii = 0; ii < iArrLen; ii++) {
        iarr[ii] = (rand() % 99) + 1;
    }

    printf("pai2xu4qian2:");
    arrToString(&iarr, iArrLen);

    // 构建大根堆
    // 父结点下标
    int tiFuJieDian = 0, tiNum = 0;
    for (int ii = 0; ii < iArrLen; ii++) {
        // 注意转换下标，数组下标和数组二叉树下标差1
        int ij = ii + 1;
        while (ij >= 1) {
            tiFuJieDian = floor(ij / 2) - 1;
            if (tiFuJieDian >= 0 && iarr[tiFuJieDian] < iarr[ij - 1]) {
                tiNum = iarr[tiFuJieDian];
                iarr[tiFuJieDian] = iarr[ij - 1];
                iarr[ij - 1] = tiNum;
            }
            ij = tiFuJieDian;
        }
    }

    printf("pai2xu4hou4:");
    arrToString(&iarr, iArrLen);

    // 堆排序
    int iLast = iArrLen - 1;
    do {
        // 大根堆堆顶的元素最大，把这个元素和数组末尾元素交换
        tiNum = iarr[0];
        iarr[0] = iarr[iLast];
        iarr[iLast] = tiNum;
        // 剩余的元素重新构建大根堆
        for (int ii = 0; ii < iLast; ii++) {
            int ij = ii + 1;
            while (ij >= 1) {
                tiFuJieDian = floor(ij / 2) - 1;
                if (tiFuJieDian >= 0 && iarr[tiFuJieDian] < iarr[ij - 1]) {
                    tiNum = iarr[tiFuJieDian];
                    iarr[tiFuJieDian] = iarr[ij - 1];
                    iarr[ij - 1] = tiNum;
                }
                ij = tiFuJieDian;
            }
        }
        iLast--;
    } while (iLast > 0);

    printf("pai2xu4hou4:");
    arrToString(&iarr, iArrLen);

    return 0;
}