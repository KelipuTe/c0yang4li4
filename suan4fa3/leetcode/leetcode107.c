#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*#####leetcode107-二叉树的层序遍历II#####*/

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
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int **levelOrderBottom(struct TreeNode *root, int *returnSize, int **returnColumnSizes) {
    // 二叉树层次遍历用队列
    struct TreeNode *pTNArrDuiLie[10000] = {NULL};
    struct TreeNode *pTNNow = NULL;
    int iTou = 0, iWei = 0, tiWei = 0;
    int iCengShu = 0;
    int **ppiarr2MeiCeng = NULL;
    int iArrMeiCengLen[1000] = {0};
    int *piarrMeiCengLen = NULL;

    if (root == NULL) {
        *returnSize = 0;
        *returnColumnSizes = NULL;

        return ppiarr2MeiCeng;
    }
    ppiarr2MeiCeng = (int **)malloc(sizeof(int *) * 1000);
    memset(ppiarr2MeiCeng, 0, sizeof(int *) * 1000);
    {
        int tiMeiCengIndex = 0, tiMeiCengLen = 0;
        pTNArrDuiLie[iWei++] = root;
        // 外层循环是树的维度
        while (iTou < iWei) {
            tiWei = iWei;
            tiMeiCengIndex = 0;
            // 计算每层遍历长度并申请内存
            tiMeiCengLen = tiWei - iTou;
            ppiarr2MeiCeng[iCengShu] = (int *)malloc(sizeof(int) * tiMeiCengLen);
            iArrMeiCengLen[iCengShu] = tiMeiCengLen;
            // 里层循环是层次维度
            while (iTou < tiWei) {
                pTNNow = pTNArrDuiLie[iTou++];
                ppiarr2MeiCeng[iCengShu][tiMeiCengIndex++] = pTNNow->val;
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
    // 倒序每层数量
    *returnSize = iCengShu;
    // printf("iCengShu:%d\n", iCengShu);
    piarrMeiCengLen = (int *)malloc(sizeof(int) * iCengShu);
    for (int i = 0; i < iCengShu; i++) {
        piarrMeiCengLen[i] = iArrMeiCengLen[iCengShu - 1 - i];
    }
    *returnColumnSizes = piarrMeiCengLen;
    // printf("piarrMeiCengLen:");
    // for (int i = 0; i < iCengShu; i++) {
    //     printf("%d,", piarrMeiCengLen[i]);
    // }
    // printf("\n");
    // 倒序每层遍历结果
    {
        int *tpMeiCeng = NULL;
        for (int i = 0; i < (int)(iCengShu / 2); i++) {
            tpMeiCeng = ppiarr2MeiCeng[i];
            ppiarr2MeiCeng[i] = ppiarr2MeiCeng[iCengShu - 1 - i];
            ppiarr2MeiCeng[iCengShu - 1 - i] = tpMeiCeng;
        }
    }
    // printf("ppiarr2MeiCeng:\n");
    // for (int i = 0; i < iCengShu; i++) {
    //     for (int j = 0; j < piarrMeiCengLen[i]; j++) {
    //         printf("%d,", ppiarr2MeiCeng[i][j]);
    //     }
    //     printf("\n");
    // }
    // printf("\n");
    return ppiarr2MeiCeng;
}

int main() {
    int parrYuanSu[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
    int iYuanSuArrLen = sizeof(parrYuanSu) / sizeof(int);
    struct TreeNode *pTNGen = NULL;
    int **ppiarr2MeiCeng = NULL;
    int iCengShu = 0;
    int *piarrMeiCengLen = NULL;

    shuZuGouZaoErChaShu(&pTNGen, &parrYuanSu, iYuanSuArrLen, 1);
    ppiarr2MeiCeng = levelOrderBottom(pTNGen, &iCengShu, &piarrMeiCengLen);

    printf("iCengShu:%d\n", iCengShu);
    printf("piarrMeiCengLen:");
    for (int i = 0; i < iCengShu; i++) {
        printf("%d,", piarrMeiCengLen[i]);
    }
    printf("\n");
    printf("ppiarr2MeiCeng:\n");
    for (int i = 0; i < iCengShu; i++) {
        for (int j = 0; j < piarrMeiCengLen[i]; j++) {
            printf("%d,", ppiarr2MeiCeng[i][j]);
        }
        printf("\n");
    }
}