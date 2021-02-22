#include <stdio.h>

/*#####leetcode35-搜索插入位置#####*/

int searchInsert(int *nums, int numsSize, int target) {
    int iLeft = 0, iRight = numsSize - 1, iMiddle = 0;
    while (iLeft <= iRight) {
        iMiddle = (int)((iLeft + iRight) / 2);
        if (target < nums[iMiddle]) {
            // 小
            if (iMiddle - 1 < 0) {
                // 位置在第一位
                return 0;
            }
            // 和分割点比一下
            if (target > nums[iMiddle - 1]) {
                return iMiddle;
            }
            // 向左缩小范围
            iRight = iMiddle - 1;
        } else if (target > nums[iMiddle]) {
            // 大
            if (iMiddle + 1 > numsSize - 1) {
                // 位置在最后一位
                return numsSize;
            }
            // 和分割点比一下
            if (target < nums[iMiddle + 1]) {
                return iMiddle + 1;
            }
            // 向右缩小范围
            iLeft = iMiddle + 1;
        } else {
            return iMiddle;
        }
    }
    return iMiddle;
}

int main() {
    // int iArrNum[] = {1, 3, 5, 6};
    // int iNumsSize = 4, iTarget = 5;

    // int iArrNum[] = {1, 3, 5, 6};
    // int iNumsSize = 4, iTarget = 2;

    int iArrNum[] = {1, 3, 5, 6};
    int iNumsSize = 4, iTarget = 7;

    // int iArrNum[] = {1, 3, 5, 6};
    // int iNumsSize = 4, iTarget = 0;
    int iResIndex = 0;

    iResIndex = searchInsert(iArrNum, iNumsSize, iTarget);
    printf("%d\n", iResIndex);
}