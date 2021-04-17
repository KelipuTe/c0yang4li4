#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/*#####leetcode15-三数之和#####*/

/**
 * @param nums 数组
 * @param numsSize 数组长度
 * @param returnSize 2维结果数组长度
 * @param returnColumnSizes 2维结果数组每行长度
 * @return 2维结果数组
 */
int **threeSum(int *nums, int numsSize, int *returnSize, int **returnColumnSizes) {
    // 返回的2维结果数组，估算的数据规模
    int **ppiarr2Res = NULL, tiDataSize = 8 * numsSize;
    if (numsSize < 3) {
        *returnSize = 0;
        return ppiarr2Res;
    }
    // 先快排
    {
        int *parrZhan = NULL, iZhanDing = 0;
        int ii = 0, ij = 0, iMidNum = 0;
        int tiStart = 0, tiEnd = 0, tiNum = 0;

        parrZhan = (int *)malloc(tiDataSize * sizeof(int));
        memset(parrZhan, 0, tiDataSize * sizeof(int));
        parrZhan[iZhanDing++] = 0;
        parrZhan[iZhanDing++] = numsSize - 1;
        while (iZhanDing > 0) {
            tiEnd = ij = parrZhan[--iZhanDing];
            tiStart = ii = parrZhan[--iZhanDing];
            iMidNum = nums[tiStart];

            if (tiStart >= tiEnd) {
                continue;
            }
            while (ij > ii) {
                if (nums[ij] < iMidNum) {
                    tiNum = nums[ii];
                    nums[ii] = nums[ij];
                    nums[ij] = tiNum;
                    for (ii = ii + 1; ii < ij; ii++) {
                        if (nums[ii] > iMidNum) {
                            tiNum = nums[ij];
                            nums[ij] = nums[ii];
                            nums[ii] = tiNum;
                            break;
                        }
                    }
                }
                ij--;
            }
            parrZhan[iZhanDing++] = tiStart;
            parrZhan[iZhanDing++] = ii;
            parrZhan[iZhanDing++] = ii + 1;
            parrZhan[iZhanDing++] = tiEnd;
        }
    }
    // 用快排之后的有序数据求解
    ppiarr2Res = (int **)malloc(tiDataSize * sizeof(int *));
    memset(ppiarr2Res, 0, tiDataSize * sizeof(int *));
    *returnSize = 0;
    *returnColumnSizes = (int *)malloc(tiDataSize * sizeof(int));
    memset(*returnColumnSizes, 0, tiDataSize * sizeof(int));
    {
        int ii = 0, ij = 0, ik = 0, tiSum = 0;
        // 每次循环固定一个数，然后用一前一后两个指针遍历剩下的数
        for (ii = 0; ii < numsSize; ++ii) {
            // 结果需要去重，所以如果循环固定的数和上次一样就跳过
            if (ii > 0 && nums[ii] == nums[ii - 1]) {
                continue;
            }
            ij = ii + 1;
            ik = numsSize - 1;
            {
                while (ij < ik) {
                    tiSum = nums[ii] + nums[ij] + nums[ik];
                    if (tiSum > 0) {
                        // 和大于0，需要更小的数，右指针左移
                        --ik;
                    } else if (tiSum == 0) {
                        // 和等于0，记录结果
                        ppiarr2Res[*returnSize] = (int *)malloc(3 * sizeof(int));
                        ppiarr2Res[*returnSize][0] = nums[ii];
                        ppiarr2Res[*returnSize][1] = nums[ij];
                        ppiarr2Res[*returnSize][2] = nums[ik];
                        (*returnColumnSizes)[*returnSize] = 3;
                        ++(*returnSize);
                        // 结果需要去重，这里两边指针移动的时候，也要处理相同的数字
                        while (ij < ik && nums[ij] == nums[ij + 1]) {
                            ++ij;
                        }
                        while (ij < ik && nums[ik] == nums[ik - 1]) {
                            --ik;
                        }
                        // 最后左指针移动一位，继续寻找
                        ++ij;
                    } else {
                        // 和小于0，需要更大的数，左指针右移
                        ++ij;
                    }
                }
            }
        }
    }

    return ppiarr2Res;
}

int main() {
    int iarr[20] = {0};
    int iArrLen = 20;
    int **ppiarr2Res = NULL;
    int iResLen = 0;
    int *piarrResEachLen = NULL;

    // srand(time(NULL));
    // for (int ii = 0; ii < iArrLen; ii++) {
    //     iarr[ii] = (rand() % 20) - 10;
    // }

    // for (int ii = 0; ii < iArrLen; ii++) {
    //     printf("%d,", iarr[ii]);
    // }
    // printf("\n");

    ppiarr2Res = threeSum(iarr, iArrLen, &iResLen, &piarrResEachLen);

    for (int ii = 0; ii < iResLen; ++ii) {
        for (int ij = 0; ij < piarrResEachLen[ii]; ++ij) {
            printf("%d,", ppiarr2Res[ii][ij]);
        }
        printf("\n");
    }
}