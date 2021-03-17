#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*#####二叉排序树#####*/

// 二叉树结点
typedef struct ErChaShuJieDian {
    // 结点值
    int iShuZhi;
    // 左子树结点
    struct ErChaShuJieDian *pECSJDZuo;
    // 右子树结点
    struct ErChaShuJieDian *pECSJDYou;
} ECSJD;

// 输出数组
extern void shuChuShuZu(int *, int);
// 插入结点
extern void chaRuJieDian(ECSJD **, int);
// 删除结点
extern void shanChuJieDian(ECSJD *, int);
// 中序遍历
extern void zhongXuBianLi(ECSJD *);

int main() {
    // 根节点指针
    ECSJD *pECSJDGen = NULL;
    int iarrDaiPaiXu[10];
    int iarrDaiPaiXuLen = 10;

    srand(time(NULL));
    for (int i = 0; i < iarrDaiPaiXuLen; i++) {
        iarrDaiPaiXu[i] = rand() % 99 + 1;
        chaRuJieDian(&pECSJDGen, iarrDaiPaiXu[i]);
    }

    printf("dai4pai2xu4:");
    shuChuShuZu(&iarrDaiPaiXu, iarrDaiPaiXuLen);

    printf("zhong1xu4bian4li4:");
    zhongXuBianLi(pECSJDGen);
    printf("\n");

    shanChuJieDian(pECSJDGen, iarrDaiPaiXu[4]);

    printf("zhong1xu4bian4li4:");
    zhongXuBianLi(pECSJDGen);
    printf("\n");

    return 0;
}

void shuChuShuZu(int *iarrDaiPaiXu, int iArrDaiPaiXuLen) {
    for (int i = 0; i < iArrDaiPaiXuLen; i++) {
        printf("%d,", iarrDaiPaiXu[i]);
    }
    printf("\n");
}

void chaRuJieDian(ECSJD **ppECSJDGen, int iChaRuZhi) {
    // 记录要插入的结点的父结点
    ECSJD *pECSJDLast = NULL;
    ECSJD *tpECSJD = NULL;

    if (*ppECSJDGen == NULL) {
        *ppECSJDGen = (ECSJD *)malloc(sizeof(ECSJD));
        (*ppECSJDGen)->iShuZhi = iChaRuZhi;
        (*ppECSJDGen)->pECSJDZuo = NULL;
        (*ppECSJDGen)->pECSJDYou = NULL;
    } else {
        pECSJDLast = tpECSJD = *ppECSJDGen;
        while (tpECSJD != NULL) {
            if (iChaRuZhi < tpECSJD->iShuZhi) {
                pECSJDLast = tpECSJD;
                tpECSJD = tpECSJD->pECSJDZuo;
            } else if (iChaRuZhi > tpECSJD->iShuZhi) {
                pECSJDLast = tpECSJD;
                tpECSJD = tpECSJD->pECSJDYou;
            } else {
                // 要插入的值已经存在
                break;
            }
        }
        // 如果要插入的值不存在
        // pECSJDLast会指向将要插入的结点的父结点，tpECSJD会指向NULL
        // 否则pECSJDLast和tpECSJD相等
        if (pECSJDLast != tpECSJD) {
            tpECSJD = (ECSJD *)malloc(sizeof(ECSJD));
            tpECSJD->iShuZhi = iChaRuZhi;
            tpECSJD->pECSJDZuo = NULL;
            tpECSJD->pECSJDYou = NULL;
            // 比较一下结点应该插到哪一边
            if (iChaRuZhi < pECSJDLast->iShuZhi) {
                pECSJDLast->pECSJDZuo = tpECSJD;
            } else if (iChaRuZhi > pECSJDLast->iShuZhi) {
                pECSJDLast->pECSJDYou = tpECSJD;
            }
        }
    }
}

void shanChuJieDian(ECSJD *pECSJDGen, int iShanChuZhi) {
    // 记录要删除的结点的父结点，记录要删除的结点
    ECSJD *pECSJDLast = NULL, *pECSJDDel = NULL;
    ECSJD *tpECSJD = NULL;

    tpECSJD = pECSJDGen;
    while (tpECSJD != NULL) {
        if (iShanChuZhi < tpECSJD->iShuZhi) {
            pECSJDLast = tpECSJD;
            tpECSJD = tpECSJD->pECSJDZuo;
        } else if (iShanChuZhi > tpECSJD->iShuZhi) {
            pECSJDLast = tpECSJD;
            tpECSJD = tpECSJD->pECSJDYou;
        } else {
            // 要删除的结点
            pECSJDDel = tpECSJD;
            break;
        }
    }
    if (pECSJDDel != NULL) {
        if (pECSJDDel->pECSJDZuo == NULL) {
            // 如果要删除的结点左子树为空，直接把右子树接上来
            if (pECSJDLast->pECSJDZuo == pECSJDDel) {
                pECSJDLast->pECSJDZuo = pECSJDDel->pECSJDYou;
            } else if (pECSJDLast->pECSJDYou == pECSJDDel) {
                pECSJDLast->pECSJDYou = pECSJDDel->pECSJDYou;
            }
            free(pECSJDDel);
        } else if (pECSJDDel->pECSJDYou == NULL) {
            // 如果要删除的结点左子树为空，直接把左子树接上来
            if (pECSJDLast->pECSJDZuo == pECSJDDel) {
                pECSJDLast->pECSJDZuo = pECSJDDel->pECSJDZuo;
            } else if (pECSJDLast->pECSJDYou == pECSJDDel) {
                pECSJDLast->pECSJDYou = pECSJDDel->pECSJDZuo;
            }
            free(pECSJDDel);
        } else {
            // 如果目标结点的左子树和右子树都存在
            // 可以从左子树中找到结点值最大的结点替代被删除的结点
            // 同理，从右子树中找到结点值最小的结点也是可行的
            pECSJDLast = pECSJDDel;
            tpECSJD = pECSJDDel->pECSJDZuo;
            while (tpECSJD->pECSJDYou != NULL) {
                pECSJDLast = tpECSJD;
                tpECSJD = tpECSJD->pECSJDYou;
            }
            // 直接把结点值最大的结点的结点值赋值到要删除的结点上
            pECSJDDel->iShuZhi = tpECSJD->iShuZhi;
            if (pECSJDLast != pECSJDDel) {
                // 如果替代结点的前驱结点不是删除结点的位置
                // 则删除结点左结点有右结点，需要考虑该右结点的左子树
                pECSJDLast->pECSJDYou = tpECSJD->pECSJDZuo;
            } else {
                // 如果替代结点的前驱结点就是删除结点的位置
                // 则删除结点左结点没有右结点，直接把该左结点的左子树接过来
                pECSJDLast->pECSJDZuo = tpECSJD->pECSJDZuo;
            }
            // 释放掉结点值最大的结点，这个结点的值已经被记录到原先要删除的结点了
            free(tpECSJD);
        }
    }
}

void zhongXuBianLi(ECSJD *pECSJDGen) {
    ECSJD *tpECSJD = pECSJDGen;

    if (tpECSJD == NULL) {
        return;
    }
    zhongXuBianLi(tpECSJD->pECSJDZuo);
    printf("%d,", tpECSJD->iShuZhi);
    zhongXuBianLi(tpECSJD->pECSJDYou);
}