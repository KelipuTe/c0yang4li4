#include <math.h>
#include <stdio.h>
#include <stdlib.h>

/*#####二叉树#####*/

// 用于标记无效的二叉树结点
#define ECSJD_NULL -2147483648

// 二叉树结点
typedef struct ErChaShuJieDian {
    // 结点值
    int iShuZhi;
    // 左子树结点
    struct ErChaShuJieDian *pECSJDZuo;
    // 右子树结点
    struct ErChaShuJieDian *pECSJDYou;
} ECSJD;

// 从数组构造二叉树
extern void shuZuGouZaoECS(ECSJD **, int *, int, int);
// 前序遍历，根左右
extern void qianXuBianLi(ECSJD *);
// 中序遍历，左根右
extern void zhongXuBianLi(ECSJD *);
// 后序遍历，左右根
extern void houXuBianLi(ECSJD *);
// 计算二叉树深度
extern int jiSuanECSShenDu(ECSJD *);
// 广度优先遍历
extern void guangDuYouXianBianLi(ECSJD *);
// 深度优先遍历
extern void shenDuYouXianBianLi(ECSJD *);

/*#####实现代码#####*/

int main() {
    // 用数组保存的二叉树结构
    int iarrYuanSu[] = {1, 2, 3, 4, 5, 6, 7, ECSJD_NULL, ECSJD_NULL, 10, 11};
    int iArrYuanSuLen = sizeof(iarrYuanSu) / sizeof(int);
    // 根节点指针
    ECSJD *pECSJDGen = NULL;

    shuZuGouZaoECS(&pECSJDGen, iarrYuanSu, iArrYuanSuLen, 1);

    printf("qian2xu4bian4li4:");
    qianXuBianLi(pECSJDGen);
    printf("\n");

    printf("zhong1xu4bian4li4:");
    zhongXuBianLi(pECSJDGen);
    printf("\n");

    printf("hou4xu4bian4li4:");
    houXuBianLi(pECSJDGen);
    printf("\n");

    printf("er4cha1shu4shen1du4:%d\n", jiSuanECSShenDu(pECSJDGen));

    printf("guang3du4you1xian1bian4li4:");
    guangDuYouXianBianLi(pECSJDGen);
    printf("\n");

    printf("shen1du4you1xian1bian4li4:");
    shenDuYouXianBianLi(pECSJDGen);
    printf("\n");

    return 0;
}

void shuZuGouZaoECS(ECSJD **tppECSJD, int *pYuanSuBiao, int iYuanSuBiaoLen, int iIndex) {
    if (iIndex <= iYuanSuBiaoLen) {
        if (pYuanSuBiao[iIndex - 1] == ECSJD_NULL) {
            // 识别无效值
            *tppECSJD = NULL;
        } else {
            *tppECSJD = (ECSJD *)malloc(sizeof(ECSJD));
            (*tppECSJD)->iShuZhi = pYuanSuBiao[iIndex - 1];
            (*tppECSJD)->pECSJDZuo = NULL;
            (*tppECSJD)->pECSJDYou = NULL;
            // 这里把这次构造的结点的左右结点传递下去，用递归的方式分别构造左右子树
            // 这里需要利用，用数组保存的二叉树结构中，父节结点与子结点的数组下标关系
            shuZuGouZaoECS(&((*tppECSJD)->pECSJDZuo), pYuanSuBiao, iYuanSuBiaoLen, iIndex * 2);
            shuZuGouZaoECS(&((*tppECSJD)->pECSJDYou), pYuanSuBiao, iYuanSuBiaoLen, iIndex * 2 + 1);
        }
    }
}

void qianXuBianLi(ECSJD *pECSJDGen) {
    ECSJD *tpECSJD = pECSJDGen;

    if (tpECSJD == NULL) {
        return;
    }
    printf("%d,", tpECSJD->iShuZhi);
    qianXuBianLi(tpECSJD->pECSJDZuo);
    qianXuBianLi(tpECSJD->pECSJDYou);
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

void houXuBianLi(ECSJD *pECSJDGen) {
    ECSJD *tpECSJD = pECSJDGen;

    if (tpECSJD == NULL) {
        return;
    }
    houXuBianLi(tpECSJD->pECSJDZuo);
    houXuBianLi(tpECSJD->pECSJDYou);
    printf("%d,", tpECSJD->iShuZhi);
}

int jiSuanECSShenDu(ECSJD *tpECSJD) {
    int iZuoShenDu = 0, iYouShenDu = 0;

    if (tpECSJD == NULL) {
        return 0;
    }
    iZuoShenDu = jiSuanECSShenDu(tpECSJD->pECSJDZuo);
    iYouShenDu = jiSuanECSShenDu(tpECSJD->pECSJDYou);

    return (int)fmax(iZuoShenDu, iYouShenDu) + 1;
}

void guangDuYouXianBianLi(ECSJD *pECSJDGen) {
    // 队列
    ECSJD *parrECSJDDuiLie[100] = {NULL};
    int iDuiLieTou = 0, iDuiLieWei = 0;
    ECSJD *tpECSJD = NULL;
    // 当前循环层数，队尾结点在队列中的位置
    int iJieDianCengShu = 1, tiCengWei = 0;

    parrECSJDDuiLie[iDuiLieWei++] = pECSJDGen;
    tpECSJD = parrECSJDDuiLie[iDuiLieTou++];
    while (iDuiLieTou <= iDuiLieWei && tpECSJD != NULL) {
        // 持续遍历，直到队列为空
        tiCengWei = iDuiLieWei;
        while (iDuiLieTou <= tiCengWei) {
            printf("%d-%d,", iJieDianCengShu, tpECSJD->iShuZhi);
            if (tpECSJD->pECSJDZuo != NULL) {
                // 左结点先入队，先遍历
                parrECSJDDuiLie[iDuiLieWei++] = tpECSJD->pECSJDZuo;
            }
            if (tpECSJD->pECSJDYou != NULL) {
                // 右结点后入队，后遍历
                parrECSJDDuiLie[iDuiLieWei++] = tpECSJD->pECSJDYou;
            }
            if (iDuiLieTou < iDuiLieWei) {
                tpECSJD = parrECSJDDuiLie[iDuiLieTou++];
            } else {
                // 控制外层遍历结束条件
                iDuiLieTou = iDuiLieWei + 1;
                tpECSJD = NULL;
            }
        }
        iJieDianCengShu++;
    }
}

void shenDuYouXianBianLi(ECSJD *pECSJDGen) {
    // 栈
    ECSJD *arrECSJDZhan[100] = {NULL};
    int iZhanDing = 0;
    ECSJD *tpECSJD = NULL;

    arrECSJDZhan[iZhanDing++] = pECSJDGen;
    tpECSJD = arrECSJDZhan[--iZhanDing];
    while (iZhanDing >= 0 && tpECSJD != NULL) {
        // 持续遍历，直到栈为空
        printf("%d,", tpECSJD->iShuZhi);
        if (tpECSJD->pECSJDYou != NULL) {
            // 右结点先入栈，后遍历
            arrECSJDZhan[iZhanDing++] = tpECSJD->pECSJDYou;
        }
        if (tpECSJD->pECSJDZuo != NULL) {
            // 左结点后入栈，先遍历
            arrECSJDZhan[iZhanDing++] = tpECSJD->pECSJDZuo;
        }
        if (iZhanDing > 1) {
            tpECSJD = arrECSJDZhan[--iZhanDing];
        } else {
            tpECSJD = NULL;
        }
    }
}