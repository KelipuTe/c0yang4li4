

/*#####leetcode15-三数之和#####*/

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int **threeSum(int *nums, int numsSize, int *returnSize, int **returnColumnSizes) {
    int arrZhan[100] = {0}, iZhanDing = 0;
    int ii = 0, ij = 0, iMidNum = 0;
    int tiStart = 0, tiEnd = 0, tiNum = 0;

    arrZhan[iZhanDing++] = 0;
    arrZhan[iZhanDing++] = numsSize - 1;
    while (iZhanDing > 0) {
        tiEnd = ij = arrZhan[--iZhanDing];
        tiStart = ii = arrZhan[--iZhanDing];
        iMidNum = iarr[tiStart];

        if (tiStart >= tiEnd) {
            return;
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
        arrZhan[iZhanDing++] = tiStart;
        arrZhan[iZhanDing++] = ii;
        arrZhan[iZhanDing++] = ii + 1;
        arrZhan[iZhanDing++] = tiEnd;
    }
}

int main() {
}