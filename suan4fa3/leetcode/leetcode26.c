#include <stdio.h>

/*#####leetcode26-删除排序数组中的重复项#####*/

int removeDuplicates(int *nums, int numsSize) {
    int i = 1, j = 1, ti = nums[0];
    if (numsSize == 0) {
        return 0;
    }
    while (i < numsSize) {
        if (ti != nums[i]) {
            ti = nums[i];
            nums[j] = nums[i];
            j++;
        }
        i++;
    }

    return j;
}

int main() {
    int iArrNum[] = {0, 0, 1, 1, 1, 2, 2, 3, 3, 4};
    int iArrLen = 10;
    int iResLen = 0;

    iResLen = removeDuplicates(iArrNum, iArrLen);
    printf("%d\n", iResLen);
}