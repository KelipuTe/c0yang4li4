#include <stdio.h>
#include <stdlib.h>

/*#####leetcode104-二叉树的最大深度#####*/

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

void shuZuGouZaoErChaShu(struct TreeNode **ppTNNow, int *parrYuanSu, int iYuanSuArrLen, int iIndex) {
    if (iIndex <= iYuanSuArrLen) {
        if (parrYuanSu[iIndex - 1] == 0) {
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

int maxDepth(struct TreeNode *root) {
    // 二叉树层次遍历用队列
    struct TreeNode *pTNArrDuiLie[10000] = {NULL};
    struct TreeNode *pTNNow = NULL;
    int iTou = 0, iWei = 0, tiWei = 0;
    int iCengShu = 0;

    if (root == NULL) {
        return 0;
    }
    pTNArrDuiLie[iWei] = root;
    iWei++;
    // 外层循环是树的维度
    while (iTou < iWei) {
        tiWei = iWei;
        // 里层循环是层次维度
        while (iTou < tiWei) {
            pTNNow = pTNArrDuiLie[iTou];
            iTou++;
            if (pTNNow->left != NULL) {
                pTNArrDuiLie[iWei] = pTNNow->left;
                iWei++;
            }
            if (pTNNow->right != NULL) {
                pTNArrDuiLie[iWei] = pTNNow->right;
                iWei++;
            }
        }
        iCengShu++;
    }

    return iCengShu;
}

int main() {
    int parrYuanSu[] = {1, 2, 3, 4, 5, 6, 7, 0, 0, 10, 11};
    int iYuanSuArrLen = sizeof(parrYuanSu) / sizeof(int);
    int iShenDu = 0;
    struct TreeNode *pTNGen = NULL;

    shuZuGouZaoErChaShu(&pTNGen, &parrYuanSu, iYuanSuArrLen, 1);
    iShenDu = maxDepth(pTNGen);
    printf("%d\n", iShenDu);
}