#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*#####leetcode119-杨辉三角II#####*/

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *getRow(int rowIndex, int *returnSize) {
    int *piarrYiCeng = NULL;

    // 这里是题目有歧义
    rowIndex++;

    if (rowIndex == 0) {
        *returnSize = 0;

        return piarrYiCeng;
    }

    piarrYiCeng = (int *)malloc(sizeof(int) * (rowIndex + 1));
    memset(piarrYiCeng, 0, sizeof(int) * (rowIndex + 1));
    for (int i = 0; i < rowIndex; i++) {
        for (int j = i; j >= 0; j--) {
            if (j == 0 || j == i) {
                piarrYiCeng[j] = 1;
            } else {
                piarrYiCeng[j] = piarrYiCeng[j - 1] + piarrYiCeng[j];
            }
        }
    }

    *returnSize = rowIndex;

    return piarrYiCeng;
}

int main() {
    int iHangShu = 3, iChangDu = 0;
    int *piarrYiCeng = NULL;

    piarrYiCeng = getRow(iHangShu, &iChangDu);
    for (int i = 0; i < iChangDu; i++) {
        printf("%d,", piarrYiCeng[i]);
    }
    printf("\n");
}