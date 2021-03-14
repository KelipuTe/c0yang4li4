#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*#####选择排序#####*/

void arrToString(int *iarr, int iArrLen) {
    for (int ii = 0; ii < iArrLen; ii++) {
        printf("%d,", iarr[ii]);
    }
    printf("\n");
}

int main() {
    int iarr[10] = {0};
    int iArrLen = 10;

    srand(time(NULL));
    for (int ii = 0; ii < iArrLen; ii++) {
        iarr[ii] = (rand() % 99) + 1;
    }

    printf("pai2xu4qian2:");
    arrToString(&iarr, iArrLen);

    // 第n次循环找到第n小的那个元素
    // 最小元素的下标
    int iMinIndex = 0, tiNum = 0;
    for (int ii = 0; ii < iArrLen; ii++) {
        iMinIndex = ii;
        for (int ij = ii; ij < iArrLen; ij++) {
            if (iarr[ij] < iarr[iMinIndex]) {
                iMinIndex = ij;
            }
        }
        // 把第n小的值和序列第n个位置的元素交换
        tiNum = iarr[ii];
        iarr[ii] = iarr[iMinIndex];
        iarr[iMinIndex] = tiNum;
    }

    printf("pai2xu4hou4:");
    arrToString(&iarr, iArrLen);

    return 0;
}