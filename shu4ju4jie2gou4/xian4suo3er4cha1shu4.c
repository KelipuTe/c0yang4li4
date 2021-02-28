#include <stdio.h>
#include <stdlib.h>

/*#####线索二叉树#####*/

// 用于标记无效的二叉树结点
#define ECSJD_NULL -2147483648

// 二叉树结点
typedef struct ErChaShuJieDian {
    // 结点值
    int iShuZhi;
    // 左标识:-1=未设置；0=前驱；1=左结点
    int iBiaoShiZuo;
    // 左子树结点
    struct ErChaShuJieDian *pECSJDZuo;
    // 右标识:-1=未设置；0=后继；1=右结点
    int iBiaoShiYou;
    // 右子树结点
    struct ErChaShuJieDian *pECSJDYou;
} ECSJD;

// 从数组构造二叉树
extern void shuZuGouZaoECS(ECSJD **, int *, int, int, ECSJD *);
// 中序遍历线索化
extern void zhongXuBianLiXianSuoHua(ECSJD *, ECSJD **);
// 中序遍历，左根右
extern void zhongXuBianLi(ECSJD *);

/*#####实现代码#####*/

int main() {
    int iarrYuanSu[] = {1, 2, 3, ECSJD_NULL, 5, ECSJD_NULL, 7, ECSJD_NULL, ECSJD_NULL, 10, 11, ECSJD_NULL, ECSJD_NULL, 14};
    int iArrYuanSuLen = sizeof(iarrYuanSu) / sizeof(int);
    // 根节点指针，保存线索化时的前驱结点
    ECSJD *pECSJDGen = NULL, *pECSJDQianQu = NULL;

    shuZuGouZaoECS(&pECSJDGen, iarrYuanSu, iArrYuanSuLen, 1, NULL);
    pECSJDQianQu = pECSJDGen;
    zhongXuBianLiXianSuoHua(pECSJDGen, &pECSJDQianQu);

    printf("zhong1xu4bian4li4:");
    zhongXuBianLi(pECSJDGen);
    printf("\n");

    return 0;
}

void shuZuGouZaoECS(ECSJD **tppECSJD, int *pYuanSuBiao, int iYuanSuBiaoLen, int iIndex, ECSJD *pECSJDLast) {
    if (iIndex <= iYuanSuBiaoLen) {
        if (pYuanSuBiao[iIndex - 1] == ECSJD_NULL) {
            *tppECSJD = NULL;
        } else {
            *tppECSJD = (ECSJD *)malloc(sizeof(ECSJD));
            (*tppECSJD)->iShuZhi = pYuanSuBiao[iIndex - 1];
            (*tppECSJD)->iBiaoShiZuo = -1;
            (*tppECSJD)->pECSJDZuo = NULL;
            (*tppECSJD)->iBiaoShiYou = -1;
            (*tppECSJD)->pECSJDYou = NULL;
            if (pECSJDLast != NULL) {
                if (pECSJDLast->pECSJDZuo == *tppECSJD) {
                    pECSJDLast->iBiaoShiZuo = 1;
                } else if (pECSJDLast->pECSJDYou == *tppECSJD) {
                    pECSJDLast->iBiaoShiYou = 1;
                }
            }
            shuZuGouZaoECS(&((*tppECSJD)->pECSJDZuo), pYuanSuBiao, iYuanSuBiaoLen, iIndex * 2, *tppECSJD);
            shuZuGouZaoECS(&((*tppECSJD)->pECSJDYou), pYuanSuBiao, iYuanSuBiaoLen, iIndex * 2 + 1, *tppECSJD);
        }
    }
}

void zhongXuBianLiXianSuoHua(ECSJD *tpECSJD, ECSJD **ppECSJDQianQu) {
    if (tpECSJD == NULL) {
        return;
    }
    // 处理左结点
    if (tpECSJD->iBiaoShiZuo == 1) {
        // 有左结点
        zhongXuBianLiXianSuoHua(tpECSJD->pECSJDZuo, ppECSJDQianQu);
    } else if (tpECSJD->iBiaoShiZuo == -1) {
        // 没设置左结点
        if (*ppECSJDQianQu != NULL) {
            tpECSJD->iBiaoShiZuo = 0;
            tpECSJD->pECSJDZuo = *ppECSJDQianQu;
        }
    }
    // 判断前驱结点有没有设置过后继结点
    if (*ppECSJDQianQu != NULL && (*ppECSJDQianQu)->iBiaoShiYou == -1) {
        (*ppECSJDQianQu)->iBiaoShiYou = 0;
        (*ppECSJDQianQu)->pECSJDYou = tpECSJD;
    }
    // 登记自己为新的前驱结点
    *ppECSJDQianQu = tpECSJD;
    // 处理右结点
    if (tpECSJD->iBiaoShiYou == 1) {
        // 有右结点
        zhongXuBianLiXianSuoHua(tpECSJD->pECSJDYou, ppECSJDQianQu);
    }
}

void zhongXuBianLi(ECSJD *pECSJDGen) {
    ECSJD *tpECSJD = pECSJDGen;

    if (tpECSJD == NULL) {
        return;
    }
    if (tpECSJD->iBiaoShiZuo == 1) {
        zhongXuBianLi(tpECSJD->pECSJDZuo);
    }
    printf("%d,", tpECSJD->iShuZhi);
    if (tpECSJD->iBiaoShiYou == 1) {
        zhongXuBianLi(tpECSJD->pECSJDYou);
    }
}