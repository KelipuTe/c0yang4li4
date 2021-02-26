#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*#####leetcode199-二叉树的右视图#####*/

// 定义空节点
#define TREE_NODE_NULL -999

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

void shuZuGouZaoErChaShu(struct TreeNode **ppTNNow, int *parrYuanSu, int iYuanSuArrLen, int iIndex) {
    if (iIndex <= iYuanSuArrLen) {
        if (parrYuanSu[iIndex - 1] == TREE_NODE_NULL) {
            *ppTNNow = NULL;

            return;
        } else {
            *ppTNNow = (struct TreeNode *)malloc(sizeof(struct TreeNode));
            (*ppTNNow)->val = parrYuanSu[iIndex - 1];
            (*ppTNNow)->left = NULL;
            (*ppTNNow)->right = NULL;
            shuZuGouZaoErChaShu(&((*ppTNNow)->left), parrYuanSu, iYuanSuArrLen, iIndex * 2);
            shuZuGouZaoErChaShu(&((*ppTNNow)->right), parrYuanSu, iYuanSuArrLen, iIndex * 2 + 1);
        }
    }
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *rightSideView(struct TreeNode *root, int *returnSize) {
    struct TreeNode *pTNArrDuiLie[10000] = {NULL};
    struct TreeNode *pTNNow = NULL;
    int iTou = 0, iWei = 0, tiWei = 0;
    int iCengShu = 0;
    int *piarrMeiCengWei = NULL;

    if (root == NULL) {
        *returnSize = 0;

        return piarrMeiCengWei;
    }
    piarrMeiCengWei = (int *)malloc(sizeof(int) * 1000);
    memset(piarrMeiCengWei, 0, sizeof(int) * 1000);
    {
        int tiMeiCengIndex = 0, tiMeiCengLen = 0;
        pTNArrDuiLie[iWei++] = root;
        // 外层循环是树的维度
        while (iTou < iWei) {
            tiWei = iWei;
            tiMeiCengIndex = 0;
            // 计算每层遍历长度并申请内存
            tiMeiCengLen = tiWei - iTou;
            // 里层循环是层次维度
            while (iTou < tiWei) {
                pTNNow = pTNArrDuiLie[iTou++];
                piarrMeiCengWei[iCengShu] = pTNNow->val;
                if (pTNNow->left != NULL) {
                    pTNArrDuiLie[iWei++] = pTNNow->left;
                }
                if (pTNNow->right != NULL) {
                    pTNArrDuiLie[iWei++] = pTNNow->right;
                }
            }
            iCengShu++;
        }
    }
    *returnSize = iCengShu;

    return piarrMeiCengWei;
}

int main() {
    int parrYuanSu[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
    int iYuanSuArrLen = sizeof(parrYuanSu) / sizeof(int);
    struct TreeNode *pTNGen = NULL;
    int *piarrMeiCengWei = NULL;
    int iCengShu = 0;

    shuZuGouZaoErChaShu(&pTNGen, &parrYuanSu, iYuanSuArrLen, 1);
    piarrMeiCengWei = rightSideView(pTNGen, &iCengShu);
    for (int i = 0; i < iCengShu; i++) {
        printf("%d,", piarrMeiCengWei[i]);
    }
    printf("\n");
}