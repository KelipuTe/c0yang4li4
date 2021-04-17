#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/*#####leetcode169-多数元素#####*/

int majorityElement(int *nums, int numsSize) {
    // 由于题目规定多数元素的数量超过数组长度的一半，所以如果遇到不一样的数字就同时移除这两个数字，最后多数元素一定多出来
    // 可以借助反着玩的抽鬼牌理解这个过程
    int iNum = nums[0], iCount = 1;
    for (int ii = 1; ii < numsSize; ++ii) {
        if (nums[ii] == iNum) {
            ++iCount;
        } else {
            --iCount;
        }
        if (iCount <= 0) {
            iNum = nums[++ii];
            iCount = 1;
        }
    }
    return iNum;
}

int main() {
    // int iarr[] = {};
    int iarr[] = {1, 2, 1, 3, 1, 2, 1, 2, 1};
    int iArrLen = 9;
    int iRes = 0;

    iRes = majorityElement(iarr, iArrLen);
    printf("%d\n", iRes);
}