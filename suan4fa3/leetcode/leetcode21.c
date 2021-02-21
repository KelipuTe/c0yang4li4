#include <stdio.h>
#include <stdlib.h>

/*#####leetcode21-合并两个有序链表#####*/

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

struct ListNode *mergeTwoLists(struct ListNode *l1, struct ListNode *l2) {
    struct ListNode *pTou = NULL, *pNow = NULL, *pNowL1 = l1, *pNowL2 = l2;

    if (pNowL1 == NULL) {
        return pNowL2;
    }
    if (pNowL2 == NULL) {
        return pNowL1;
    }
    // 确定头
    if (pNowL1->val < pNowL2->val) {
        pTou = pNowL1;
        pNow = pNowL1;
        pNowL1 = pNowL1->next;
    } else {
        pTou = pNowL2;
        pNow = pNowL2;
        pNowL2 = pNowL2->next;
    }
    while (1) {
        // 其中一条链表已经到尾部
        if (pNowL1 == NULL) {
            pNow->next = pNowL2;
            break;
        }
        if (pNowL2 == NULL) {
            pNow->next = pNowL1;
            break;
        }
        // 两条链表都没有到尾部
        if (pNowL1->val < pNowL2->val) {
            pNow->next = pNowL1;
            pNow = pNowL1;
            pNowL1 = pNowL1->next;
        } else {
            pNow->next = pNowL2;
            pNow = pNowL2;
            pNowL2 = pNowL2->next;
        }
    }

    return pTou;
}

int main() {
    // int iArrNum1[] = {2, 3, 4};
    // int iNumLen1 = 3;
    // int iArrNum2[] = {4, 5, 6};
    // int iNumLen2 = 3;
    // int iArrNum1[] = {2, 3, 4};
    // int iNumLen1 = 3;
    // int iArrNum2[] = {5};
    // int iNumLen2 = 1;
    int iArrNum1[] = {2, 3, 4};
    int iNumLen1 = 3;
    int iArrNum2[] = {4, 4, 5, 6};
    int iNumLen2 = 4;
    struct ListNode *pLN1 = NULL, *pLN2 = NULL, *pLN3 = NULL;

    pLN1 = shuZuGouZaoLianBiao(iArrNum1, iNumLen1);
    shuChuLianBiao(pLN1);
    pLN2 = shuZuGouZaoLianBiao(iArrNum2, iNumLen2);
    shuChuLianBiao(pLN2);
    pLN3 = mergeTwoLists(pLN1, pLN2);
    shuChuLianBiao(pLN3);
}