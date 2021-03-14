#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*#####归并排序#####*/

void arrToString(int *iarr, int iArrLen) {
    for (int ii = 0; ii < iArrLen; ii++) {
        printf("%d,", iarr[ii]);
    }
    printf("\n");
}

// 归并排序分组
void guiBinPaiXu(int *iarr, int iStart, int iEnd) {
    int iMid = 0;
    if (iStart < iEnd) {
        // 数组二等分，分别处理
        iMid = floor((iStart + iEnd) / 2);
        guiBinPaiXu(iarr, iStart, iMid);
        guiBinPaiXu(iarr, iMid + 1, iEnd);
        heBin(iarr, iStart, iMid, iEnd);
    }
}

// 归并排序合并
void heBin(int *iarr, int iStart, int iMid, int iEnd) {
    int ii = iStart, ij = iMid + 1, ik = iStart;
    // 使用一个临时数组保存本次归并的结果
    int tPaiXuArr[10];
    while (ii < iMid + 1 && ij < iEnd + 1) {
        // 当两个序列都没有到头，需要比较哪个序列的第一个元素更小
        if (iarr[ii] >= iarr[ij]) {
            tPaiXuArr[ik++] = iarr[ij++];
        } else {
            tPaiXuArr[ik++] = iarr[ii++];
        }
    }
    while (ii < iMid + 1) {
        // 当前面的序列已经到头，直接把后面序列的元素依次赋值
        tPaiXuArr[ik++] = iarr[ii++];
    }
    while (ij < iEnd + 1) {
        // 当后面的序列已经到头，直接把前面序列的元素依次赋值
        tPaiXuArr[ik++] = iarr[ij++];
    }
    for (ii = iStart; ii < iEnd + 1; ii++) {
        // 把排序好的序列替换到原序列的位置
        iarr[ii] = tPaiXuArr[ii];
    }
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

    guiBinPaiXu(&iarr, 0, iArrLen - 1);

    printf("pai2xu4hou4:");
    arrToString(&iarr, iArrLen);

    return 0;
}