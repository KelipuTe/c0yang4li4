#include <stdio.h>

/*#####leetcode27-移除元素#####*/

int removeElement(int *nums, int numsSize, int val) {
    int i = 0, j = 0;
    if (numsSize == 0) {
        return 0;
    }
    while (i < numsSize) {
        if (val != nums[i]) {
            nums[j] = nums[i];
            j++;
        }
        i++;
    }

    return j;
}

int main() {
    // int iArrNum[] = {0};
    // int iArrLen = 0;
    // int iArrNum[] = {3, 3};
    // int iArrLen = 2;
    int iArrNum[] = {3, 2, 23};
    int iArrLen = 2;
    int iNum = 3, iResLen = 0;

    iResLen = removeElement(iArrNum, iArrLen, iNum);
    printf("%d\n", iResLen);
}