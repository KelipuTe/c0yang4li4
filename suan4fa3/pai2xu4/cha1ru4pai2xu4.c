#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*#####插入排序#####*/

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

    // 认为第一个元素有序，排序从第二个元素开始
    for (int ii = 1; ii < iArrLen; ii++) {
        int ij = ii;
        // 本次循环的待排序元素
        int tiNum = iarr[ij];
        while (ij > 0 && tiNum < iarr[ij - 1]) {
            // 如果待排序元素比前的元素面小，就把前面的元素往后移一位
            iarr[ij] = iarr[ij - 1];
            ij--;
        }
        // 将待排序元素插入有序序列
        iarr[ij] = tiNum;
    }

    printf("pai2xu4hou4:");
    arrToString(&iarr, iArrLen);

    return 0;
}