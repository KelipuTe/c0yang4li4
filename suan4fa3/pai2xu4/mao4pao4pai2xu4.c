#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*#####冒泡排序#####*/

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

    // 记录最后一个被交换的元素的位置
    // 无论是升序排序还是降序排序，每轮比较结束之后，最后一个值一定是最大或者最小值，后续的循环就不需要进行比较了
    int iZuiHouJiaoHuan = iArrLen - 1;
    int tiZuiHouJiaoHuan = iZuiHouJiaoHuan;
    // 判断是否有元素交换
    int ibJiaoHuan = 0, tiNum = 0;
    for (int ii = 0; ii < iArrLen - 1; ii++) {
        tiZuiHouJiaoHuan = iZuiHouJiaoHuan;
        ibJiaoHuan = 0;
        // 只需要比较到最后一个被交换的元素的位置
        for (int ij = 0; ij < tiZuiHouJiaoHuan; ij++) {
            if (iarr[ij] > iarr[ij + 1]) {
                // 如果前面的元素大，就交换位置
                tiNum = iarr[ij];
                iarr[ij] = iarr[ij + 1];
                iarr[ij + 1] = tiNum;
                ibJiaoHuan = 1;
                iZuiHouJiaoHuan = ij;
            }
        }
        if (ibJiaoHuan == 0) {
            // 如果一轮排序没有元素被交换，则序列已经有序
            break;
        }
    }

    printf("pai2xu4hou4:");
    arrToString(&iarr, iArrLen);

    return 0;
}