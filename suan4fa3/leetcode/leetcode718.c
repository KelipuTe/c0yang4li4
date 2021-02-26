#include <stdio.h>
#include <stdlib.h>

/*#####leetcode718-最长重复子数组#####*/

int findLength(int *A, int ASize, int *B, int BSize) {
    int iarr2DongTaiGuiHua[1000][1000] = {0};
    int iMaxLen = 0;

    // 数组A作为列，数组B作为行
    // 第一列
    for (int i = 0; i < ASize; i++) {
        if (A[i] == B[0]) {
            iarr2DongTaiGuiHua[i][0] = 1;
        } else {
            iarr2DongTaiGuiHua[i][0] = 0;
        }
        if (iarr2DongTaiGuiHua[i][0] > iMaxLen) {
            iMaxLen = iarr2DongTaiGuiHua[i][0];
        }
    }
    // 第一行
    for (int j = 0; j < BSize; j++) {
        if (A[0] == B[j]) {
            iarr2DongTaiGuiHua[0][j] = 1;
        } else {
            iarr2DongTaiGuiHua[0][j] = 0;
        }
        if (iarr2DongTaiGuiHua[0][j] > iMaxLen) {
            iMaxLen = iarr2DongTaiGuiHua[0][j];
        }
    }
    // 动态规划
    for (int i = 1; i < ASize; i++) {
        for (int j = 1; j < BSize; j++) {
            if (A[i] == B[j]) {
                iarr2DongTaiGuiHua[i][j] = iarr2DongTaiGuiHua[i - 1][j - 1] + 1;
            } else {
                iarr2DongTaiGuiHua[i][j] = 0;
            }
            if (iarr2DongTaiGuiHua[i][j] > iMaxLen) {
                iMaxLen = iarr2DongTaiGuiHua[i][j];
            }
        }
    }

    // for (int i = 0; i < ASize; i++) {
    //     for (int j = 0; j < BSize; j++) {
    //         printf("%d,", iarr2DongTaiGuiHua[i][j]);
    //     }
    //     printf("\n");
    // }

    return iMaxLen;
}

int main() {
    int iarr1[] = {1, 2, 3, 2, 1}, iarr2[] = {3, 2, 1, 4, 7};
    int iArr1Len = sizeof(iarr1) / sizeof(int), iArr2Len = sizeof(iarr2) / sizeof(int);
    int iMaxLen = 0;

    iMaxLen = findLength(iarr1, iArr1Len, iarr2, iArr2Len);
    printf("%d\n", iMaxLen);
}