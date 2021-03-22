#include <stdio.h>

/*#####回溯-全排列#####*/

void quanPaiLie(int *piarr, int iArrLen, int ik) {
    // 每轮递归固定第ik位置的数字，然后处理前面的部分
    if (ik == 1) {
        for (int ii = 0; ii < iArrLen; ii++) {
            printf("%d,", piarr[ii]);
        }
        printf("\n");
    }
    int ti = 0;
    for (int ii = 0; ii < ik; ii++) {
        // 依次把前面的数字换到第ik位
        ti = piarr[ii];
        piarr[ii] = piarr[ik - 1];
        piarr[ik - 1] = ti;
        // 这里递归进去，所有的输出第ik位都是一样的
        quanPaiLie(piarr, iArrLen, ik - 1);
        // 再换回去，下一轮循环换另外一个过来
        ti = piarr[ii];
        piarr[ii] = piarr[ik - 1];
        piarr[ik - 1] = ti;
    }
}

int main() {
    int iarr[] = {1, 2, 3, 4};
    int iArrLen = 4;
    quanPaiLie(iarr, iArrLen, iArrLen);

    return 0;
}