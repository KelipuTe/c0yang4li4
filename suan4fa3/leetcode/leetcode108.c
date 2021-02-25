#include <stdio.h>
#include <stdlib.h>

/*#####leetcode108-将有序数组转换为二叉搜索树#####*/

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

struct TreeNode *sortedArrayToBST(int *nums, int numsSize) {
    struct TreeNode *tpTN = NULL;
    int iChaRuZhiIndex = 0;

    if (nums == NULL || numsSize == 0) {
        return NULL;
    }
    // 取中点，将数组一分为二
    iChaRuZhiIndex = (int)(numsSize / 2);
    tpTN = (struct TreeNode *)malloc(sizeof(struct TreeNode));
    tpTN->val = nums[iChaRuZhiIndex];
    tpTN->left = sortedArrayToBST(nums, iChaRuZhiIndex);
    tpTN->right = sortedArrayToBST(nums + iChaRuZhiIndex + 1, numsSize - iChaRuZhiIndex - 1);

    return tpTN;
}

int main() {
    int parrYuanSu[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
    int iYuanSuArrLen = sizeof(parrYuanSu) / sizeof(int);
    struct TreeNode *pTNGen = NULL;

    pTNGen = sortedArrayToBST(parrYuanSu, iYuanSuArrLen);
}