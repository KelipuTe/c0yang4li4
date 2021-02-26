#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*#####leetcode118-杨辉三角#####*/

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int **generate(int numRows, int *returnSize, int **returnColumnSizes) {
    int **ppiarr2MeiCeng = NULL;
    int *piarrMeiCengLen = NULL;

    if (numRows == 0) {
        *returnSize = 0;
        *returnColumnSizes = NULL;

        return ppiarr2MeiCeng;
    }

    ppiarr2MeiCeng = (int **)malloc(sizeof(int *) * numRows);
    memset(ppiarr2MeiCeng, 0, sizeof(int *) * numRows);
    piarrMeiCengLen = (int *)malloc(sizeof(int) * numRows);

    for (int i = 0; i < numRows; i++) {
        piarrMeiCengLen[i] = i + 1;
        ppiarr2MeiCeng[i] = (int *)malloc(sizeof(int) * (i + 1));
        for (int j = 0; j <= i; j++) {
            if (j == 0 || j == i) {
                ppiarr2MeiCeng[i][j] = 1;
            } else {
                ppiarr2MeiCeng[i][j] = ppiarr2MeiCeng[i - 1][j - 1] + ppiarr2MeiCeng[i - 1][j];
            }
        }
    }

    *returnSize = numRows;
    *returnColumnSizes = piarrMeiCengLen;

    return ppiarr2MeiCeng;
}

int main() {
    int iHangShu = 5, iCengShu = 0;
    int **ppiarr2MeiCeng = NULL;
    int *piarrMeiCengLen = NULL;

    ppiarr2MeiCeng = generate(iHangShu, &iCengShu, &piarrMeiCengLen);
    printf("rows:%d\n", iCengShu);
    for (int i = 0; i < iCengShu; i++) {
        printf("line len:%d\n", piarrMeiCengLen[i]);
        for (int j = 0; j <= i; j++) {
            printf("%d,", ppiarr2MeiCeng[i][j]);
        }
        printf("\n");
    }
}