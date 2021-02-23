#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*#####leetcode66-加一#####*/

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *plusOne(int *digits, int digitsSize, int *returnSize) {
    int *piArrRes = NULL;
    int ibJin4Wei4 = 0;

    // 最后一位+1
    digits[digitsSize - 1]++;
    for (int i = digitsSize - 1; i >= 0; i--) {
        if (digits[i] == 10) {
            if (i > 0) {
                digits[i] = 0;
                digits[i - 1]++;
            } else {
                // 第一位要进位的情况
                digits[i] = 0;
                ibJin4Wei4 = 1;
            }
        }
    }

    if (ibJin4Wei4 == 1) {
        // 如果第一位要进位，那就要多一个int的位置
        *returnSize = digitsSize + 1;
        piArrRes = (int *)malloc(sizeof(int) * (digitsSize + 1));
        memset(piArrRes, 0, sizeof(int) * (digitsSize + 1));
        piArrRes[0] = 1;
        for (int i = 0; i < digitsSize; i++) {
            piArrRes[i + 1] = digits[i];
        }
    } else {
        *returnSize = digitsSize;
        piArrRes = (int *)malloc(sizeof(int) * digitsSize);
        memset(piArrRes, 0, sizeof(int) * digitsSize);
        for (int i = 0; i < digitsSize; i++) {
            piArrRes[i] = digits[i];
        }
    }

    return piArrRes;
}

int main() {
    // int iArrNum[] = {9, 5};
    // int iArrLen = 2;
    int iArrNum[] = {9};
    int iArrLen = 1;
    int iResLen = 0;
    int *piArrRes = NULL;

    piArrRes = plusOne(iArrNum, iArrLen, &iResLen);
    for (int i = 0; i < iResLen; i++) {
        printf("%d,", piArrRes[i]);
    }
}