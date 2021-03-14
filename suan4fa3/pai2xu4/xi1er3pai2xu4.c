#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*#####希尔排序#####*/

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

    // 按一定的跨度分组，[0,0+n,0+2n,...]一组
    int iRange = floor(iArrLen / 2);
    int tiNum = 0;
    while (iRange > 0) {
        // 组内进行插入排序
        for (int ii = iRange; ii < iArrLen; ii++) {
            tiNum = iarr[ii];
            int ij = ii - iRange;
            while (ij >= 0 && iarr[ij] > tiNum) {
                iarr[ij + iRange] = iarr[ij];
                ij -= iRange;
            }
            iarr[ij + iRange] = tiNum;
        }
        // 重新设置一个更小的跨度
        iRange = floor(iRange / 2);
    }

    printf("pai2xu4hou4:");
    arrToString(&iarr, iArrLen);

    return 0;
}