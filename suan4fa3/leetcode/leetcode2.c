#include <stdio.h>
#include <stdlib.h>

/*#####leetcode2-两数相加#####*/

// 单链表结点
struct ListNode {
    int val;
    struct ListNode *next;
};

// 用数组构造链表
struct ListNode *shuZuGouZaoLianBiao(int iArrNum[], int iNumLen) {
    struct ListNode *pTou = NULL, *pNow = NULL, *tpLN = NULL;

    for (int i = 0; i < iNumLen; i++) {
        tpLN = (struct ListNode *)malloc(sizeof(struct ListNode));
        tpLN->val = iArrNum[i];
        tpLN->next = NULL;
        if (pNow == NULL) {
            pTou = pNow = tpLN;
        } else {
            pNow->next = tpLN;
            pNow = tpLN;
        }
    }

    return pTou;
}

// 输出链表
void shuChuLianBiao(struct ListNode *pLN) {
    struct ListNode *pNow = pLN;

    while (pNow != NULL) {
        printf("%d,", pNow->val);
        pNow = pNow->next;
    }
    printf("\n");
}

struct ListNode *addTwoNumbers(struct ListNode *l1, struct ListNode *l2) {
    int iLVal1 = 0, iLVal2 = 0, iLNow = 0, iJinWei = 0;
    struct ListNode *pNowL1 = l1, *pNowL2 = l2, *pTou = NULL, *pNow = NULL, *tpLN = NULL;

    do {
        if (pNowL1 != NULL) {
            iLVal1 = pNowL1->val;
            pNowL1 = pNowL1->next;
        } else {
            iLVal1 = 0;
        }
        if (pNowL2 != NULL) {
            iLVal2 = pNowL2->val;
            pNowL2 = pNowL2->next;
        } else {
            iLVal2 = 0;
        }
        // 判断是否需要进位
        iLNow = iJinWei + iLVal1 + iLVal2;
        if (iLNow > 9) {
            iJinWei = 1;
            iLNow -= 10;
        } else {
            iJinWei = 0;
        }
        // 构造结点
        tpLN = (struct ListNode *)malloc(sizeof(struct ListNode));
        tpLN->val = iLNow;
        tpLN->next = NULL;
        if (pTou == NULL) {
            pTou = pNow = tpLN;
        } else {
            pNow->next = tpLN;
            pNow = tpLN;
        }
    } while (pNowL1 != NULL || pNowL2 != NULL || iJinWei > 0);

    return pTou;
}

int main() {
    int iArrNum1[] = {2, 4, 3};
    int iNumLen1 = 3;
    int iArrNum2[] = {5, 6, 4};
    int iNumLen2 = 3;
    // int iArrNum1[] = {2, 4, 3};
    // int iNumLen1 = 3;
    // int iArrNum2[] = {5, 6, 6};
    // int iNumLen2 = 3;
    // int iArrNum1[] = {2, 4, 3};
    // int iNumLen1 = 3;
    // int iArrNum2[] = {5, 6, 4, 4};
    // int iNumLen2 = 4;
    struct ListNode *pLN1 = NULL, *pLN2 = NULL, *pLN3 = NULL;

    pLN1 = shuZuGouZaoLianBiao(iArrNum1, iNumLen1);
    shuChuLianBiao(pLN1);
    pLN2 = shuZuGouZaoLianBiao(iArrNum2, iNumLen2);
    shuChuLianBiao(pLN2);
    pLN3 = addTwoNumbers(pLN1, pLN2);
    shuChuLianBiao(pLN3);
}