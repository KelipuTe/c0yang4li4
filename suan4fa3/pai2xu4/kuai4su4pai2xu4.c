#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*#####快速排序#####*/

void arrToString(int *iarr, int iArrLen) {
    for (int ii = 0; ii < iArrLen; ii++) {
        printf("%d,", iarr[ii]);
    }
    printf("\n");
}

// 快速排序分组
void kuaiSuPaiXu(int *iarr, int iStart, int iEnd) {
    int ii = iStart, ij = iEnd, tiNum = 0;
    // 设定第一个元素作为基准元素
    int iMidNum = iarr[iStart];

    if (iStart >= iEnd) {
        return;
    }
    // 这里两个循环会来回移动这个基准元素，最后基准元素会把序列分为，前半部分小于基准的，和后半部分大于基准的
    while (ij > ii) {
        // 从后往前找找一个比基准小的，和基准换位置
        if (iarr[ij] < iMidNum) {
            tiNum = iarr[ii];
            iarr[ii] = iarr[ij];
            iarr[ij] = tiNum;
            for (ii = ii + 1; ii < ij; ii++) {
                // 再从前往后找，找一个比基准大的，和基准换位置
                if (iarr[ii] > iMidNum) {
                    tiNum = iarr[ij];
                    iarr[ij] = iarr[ii];
                    iarr[ii] = tiNum;
                    break;
                }
            }
        }
        ij--;
    }
    // 上面的循环ii最后会停在基准的坐标上，递归分别处理前半部分和后半部分
    kuaiSuPaiXu(iarr, iStart, ii);
    kuaiSuPaiXu(iarr, ii + 1, iEnd);
}

// 快速排序寻找第k大的元素
int kuaiSuPaiXuK(int *iarr, int iStart, int iEnd, int iK) {
    int ii = iStart, ij = iEnd, tiNum = 0;
    int iMidNum = iarr[iStart];

    if (iStart >= iEnd) {
        return iarr[iStart];
    }
    while (ij > ii) {
        if (iarr[ij] < iMidNum) {
            tiNum = iarr[ii];
            iarr[ii] = iarr[ij];
            iarr[ij] = tiNum;
            for (ii = ii + 1; ii < ij; ii++) {
                if (iarr[ii] > iMidNum) {
                    tiNum = iarr[ij];
                    iarr[ij] = iarr[ii];
                    iarr[ii] = tiNum;
                    break;
                }
            }
        }
        ij--;
    }
    // 比较一下，确定k在那个区间内
    if (ii < iK) {
        return kuaiSuPaiXuK(iarr, ii + 1, iEnd, iK);
    } else if (ii > iK) {
        return kuaiSuPaiXuK(iarr, iStart, ii, iK);
    } else {
        return iarr[ii];
    }
}

int main() {
    // int iarr[10] = {27, 19, 17, 83, 14, 41, 96, 77, 69, 15};
    int iarr[10] = {0};
    int iArrLen = 10;
    int iK = 5;

    srand(time(NULL));
    for (int ii = 0; ii < iArrLen; ii++) {
        iarr[ii] = (rand() % 99) + 1;
    }

    printf("k=%d,num=%d\n", iK, kuaiSuPaiXuK(&iarr, 0, iArrLen - 1, iK - 1));

    printf("pai2xu4qian2:");
    arrToString(&iarr, iArrLen);

    kuaiSuPaiXu(&iarr, 0, iArrLen - 1);

    printf("pai2xu4hou4:");
    arrToString(&iarr, iArrLen);

    return 0;
}