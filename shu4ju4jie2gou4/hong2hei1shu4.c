#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*#####红黑树#####*/
// 红黑树是一种特殊的二叉排序树

// 二叉树结点
typedef struct HongHeiShuJieDian {
    // 结点值
    int iShuZhi;
    // 左子树结点
    struct HongHeiShuJieDian *pHHSJDZuo;
    // 右子树结点
    struct HongHeiShuJieDian *pHHSJDYou;
    // 父结点
    struct HongHeiShuJieDian *pHHSJDFu;
    // 结点颜色
    char cYanSe;
} HHSJD;

// 输出数组
extern void shuChuShuZu(int *, int);
// 插入结点
extern void chaRuJieDian(HHSJD **, int, HHSJD **);
// 调整树的结构
extern void tiaoZheng(HHSJD *, HHSJD **);
// 左旋，自己的右结点变自己的父结点
extern void zuoXuan();
// 右旋，自己的左结点变自己的父结点
extern void youXuan();
// 删除结点
extern void shanChuJieDian();
// 中序遍历
extern void zhongXuBianLi(HHSJD *);

int main() {
    // 根结点指针
    HHSJD *pHHSJDGen = NULL;
    int iarrDaiPaiXu[10] = {87, 29, 87, 65, 25, 33, 78, 12, 5, 85};
    int iarrDaiPaiXuLen = 10;

    srand(time(NULL));
    for (int i = 0; i < iarrDaiPaiXuLen; i++) {
        // iarrDaiPaiXu[i] = (rand() % 99) + 1;
        chaRuJieDian(&pHHSJDGen, iarrDaiPaiXu[i], &pHHSJDGen);
    }

    printf("dai4pai2xu4:");
    shuChuShuZu(iarrDaiPaiXu, iarrDaiPaiXuLen);

    printf("zhong1xu4bian4li4:");
    zhongXuBianLi(pHHSJDGen);
    printf("\n");

    // todo 删除操作未完成
    // shanChuJieDian(pHHSJDGen, iarrDaiPaiXu[4]);

    printf("zhong1xu4bian4li4:");
    zhongXuBianLi(pHHSJDGen);
    printf("\n");

    return 0;
}

void shuChuShuZu(int *iarrDaiPaiXu, int iArrDaiPaiXuLen) {
    for (int i = 0; i < iArrDaiPaiXuLen; i++) {
        printf("%d,", iarrDaiPaiXu[i]);
    }
    printf("\n");
}

void chaRuJieDian(HHSJD **tppHHSJD, int iChaRuZhi, HHSJD **tppHHSJDGen) {
    if (*tppHHSJD == NULL) {
        // 结点为空
        *tppHHSJD = (HHSJD *)malloc(sizeof(HHSJD));
        (*tppHHSJD)->iShuZhi = iChaRuZhi;
        (*tppHHSJD)->pHHSJDZuo = NULL;
        (*tppHHSJD)->pHHSJDYou = NULL;
        (*tppHHSJD)->pHHSJDFu = NULL;
        (*tppHHSJD)->cYanSe = 'h';
    } else {
        if (iChaRuZhi < (*tppHHSJD)->iShuZhi) {
            // 插入值小于结点值，插到左边
            if ((*tppHHSJD)->pHHSJDZuo != NULL) {
                // 左子树存在就递归插入
                chaRuJieDian(&((*tppHHSJD)->pHHSJDZuo), iChaRuZhi, tppHHSJDGen);
            } else {
                // 左子树不存在就构造左子树
                (*tppHHSJD)->pHHSJDZuo = (HHSJD *)malloc(sizeof(HHSJD));
                (*tppHHSJD)->pHHSJDZuo->iShuZhi = iChaRuZhi;
                (*tppHHSJD)->pHHSJDZuo->pHHSJDZuo = NULL;
                (*tppHHSJD)->pHHSJDZuo->pHHSJDYou = NULL;
                (*tppHHSJD)->pHHSJDZuo->pHHSJDFu = *tppHHSJD;
                (*tppHHSJD)->pHHSJDZuo->cYanSe = 'r';
                // 左子树插入的红结点可能会破坏红黑树，需要调整左子树
                tiaoZheng((*tppHHSJD)->pHHSJDZuo, tppHHSJDGen);
            }
        } else if (iChaRuZhi > (*tppHHSJD)->iShuZhi) {
            // 插入值大于结点值，插到右边
            if ((*tppHHSJD)->pHHSJDYou != NULL) {
                chaRuJieDian(&((*tppHHSJD)->pHHSJDYou), iChaRuZhi, tppHHSJDGen);
            } else {
                (*tppHHSJD)->pHHSJDYou = (HHSJD *)malloc(sizeof(HHSJD));
                (*tppHHSJD)->pHHSJDYou->iShuZhi = iChaRuZhi;
                (*tppHHSJD)->pHHSJDYou->pHHSJDZuo = NULL;
                (*tppHHSJD)->pHHSJDYou->pHHSJDYou = NULL;
                (*tppHHSJD)->pHHSJDYou->pHHSJDFu = *tppHHSJD;
                (*tppHHSJD)->pHHSJDYou->cYanSe = 'r';
                tiaoZheng((*tppHHSJD)->pHHSJDYou, tppHHSJDGen);
            }
        } else {
            // 插入值等于结点值，不做操作
        }
    }
}

void tiaoZheng(HHSJD *tpHHSJD, HHSJD **tppHHSJDGen) {
    // 叔叔结点
    HHSJD *tpHHSJDShu = NULL;

    while (tpHHSJD != (*tppHHSJDGen) && tpHHSJD->pHHSJDFu->cYanSe == 'r') {
        // 根结点不需要调整，父结点为红色时需要调整（如果父结点是黑色的，直接插入就行）
        if (tpHHSJD->pHHSJDFu == tpHHSJD->pHHSJDFu->pHHSJDFu->pHHSJDZuo) {
            // 父结点是祖父结点的左子树
            // 则叔叔结点是祖父结点的右子树
            tpHHSJDShu = tpHHSJD->pHHSJDFu->pHHSJDFu->pHHSJDYou;
            if (tpHHSJDShu != NULL && tpHHSJDShu->cYanSe == 'r') {
                // 叔叔结点是红色
                // 情况1：父结点和叔叔结点都是红色
                // 则父结点和叔叔结点改黑色，祖父结点改红色
                tpHHSJD->pHHSJDFu->cYanSe = 'h';
                tpHHSJDShu->cYanSe = 'h';
                tpHHSJD->pHHSJDFu->pHHSJDFu->cYanSe = 'r';
                // 因为祖父结点改了红色，可能破坏红黑树，所以需要继续判断祖父结点是否需要调整
                tpHHSJD = tpHHSJD->pHHSJDFu->pHHSJDFu;
            } else {
                // 叔叔结点是黑色（叔叔结点不存在时，就相当于是定义中的黑色叶子结点）
                if (tpHHSJD == tpHHSJD->pHHSJDFu->pHHSJDYou) {
                    // 情况2：叔叔结点是黑色，自己是父结点的右子树
                    // 父结点左旋，由于左旋后父结点变成了自己的左子树，两个红色结点相连一定破坏红黑树，所以继续判断父结点（父结点在更下层）
                    // 情况2通过这个操作实际上演变成了情况3
                    // 这里要先赋值，左旋完位置就变了
                    tpHHSJD = tpHHSJD->pHHSJDFu;
                    zuoXuan(tpHHSJD, tppHHSJDGen);
                } else {
                    // 情况3：叔叔结点是黑色，自己是父结点的左子树
                    // 父结点改黑色，祖父结点改红色，祖父结点右旋
                    tpHHSJD->pHHSJDFu->cYanSe = 'h';
                    tpHHSJD->pHHSJDFu->pHHSJDFu->cYanSe = 'r';
                    youXuan(tpHHSJD->pHHSJDFu->pHHSJDFu, tppHHSJDGen);
                }
            }
        } else {
            // 父结点是祖父结点的右子树
            // 把上面左子树的操作反过来就行了
            tpHHSJDShu = tpHHSJD->pHHSJDFu->pHHSJDFu->pHHSJDZuo;
            if (tpHHSJDShu != NULL && tpHHSJDShu->cYanSe == 'r') {
                // 叔叔结点是红色
                // 情况1：父结点和叔叔结点都是红色
                tpHHSJD->pHHSJDFu->cYanSe = 'h';
                tpHHSJDShu->cYanSe = 'h';
                tpHHSJD->pHHSJDFu->pHHSJDFu->cYanSe = 'r';
                tpHHSJD = tpHHSJD->pHHSJDFu->pHHSJDFu;
            } else {
                // 叔叔结点是黑色
                if (tpHHSJD == tpHHSJD->pHHSJDFu->pHHSJDZuo) {
                    // 情况2：叔叔结点是黑色，自己是父结点的左子树
                    // 父结点右旋
                    tpHHSJD = tpHHSJD->pHHSJDFu;
                    youXuan(tpHHSJD, tppHHSJDGen);
                } else {
                    // 情况3：叔叔结点是黑色，自己是父结点的右子树
                    // 父结点改黑色，祖父结点改红色，祖父结点左旋
                    tpHHSJD->pHHSJDFu->cYanSe = 'h';
                    tpHHSJD->pHHSJDFu->pHHSJDFu->cYanSe = 'r';
                    zuoXuan(tpHHSJD->pHHSJDFu->pHHSJDFu, tppHHSJDGen);
                }
            }
        }
    }
    // 根结点的颜色调整为黑色
    (*tppHHSJDGen)->cYanSe = 'h';
}

void zuoXuan(HHSJD *tpHHSJD, HHSJD **tppHHSJDGen) {
    HHSJD *tpHHSJDFu = tpHHSJD->pHHSJDFu;
    HHSJD *tpHHSJDYou = tpHHSJD->pHHSJDYou;
    HHSJD *tpHHSJDYouZuo = tpHHSJDYou->pHHSJDZuo;

    if (tpHHSJD == *tppHHSJDGen) {
        *tppHHSJDGen = tpHHSJDYou;
    }
    tpHHSJDYou->pHHSJDFu = tpHHSJDFu;
    tpHHSJDYou->pHHSJDZuo = tpHHSJD;
    tpHHSJD->pHHSJDFu = tpHHSJDYou;
    if (tpHHSJDFu != NULL) {
        if (tpHHSJD == tpHHSJDFu->pHHSJDZuo) {
            tpHHSJDFu->pHHSJDZuo = tpHHSJDYou;
        } else if (tpHHSJD == tpHHSJDFu->pHHSJDYou) {
            tpHHSJDFu->pHHSJDYou = tpHHSJDYou;
        }
    }
    tpHHSJD->pHHSJDYou = tpHHSJDYouZuo;
    if (tpHHSJDYouZuo != NULL) {
        tpHHSJDYouZuo->pHHSJDFu = tpHHSJD;
    }
}

void youXuan(HHSJD *tpHHSJD, HHSJD **tppHHSJDGen) {
    HHSJD *tpHHSJDFu = tpHHSJD->pHHSJDFu;
    HHSJD *tpHHSJDZuo = tpHHSJD->pHHSJDZuo;
    HHSJD *tpHHSJDZuoYou = tpHHSJDZuo->pHHSJDYou;

    if (tpHHSJD == *tppHHSJDGen) {
        *tppHHSJDGen = tpHHSJDZuo;
    }
    tpHHSJDZuo->pHHSJDFu = tpHHSJDFu;
    tpHHSJDZuo->pHHSJDYou = tpHHSJD;
    tpHHSJD->pHHSJDFu = tpHHSJDZuo;
    if (tpHHSJDFu != NULL) {
        if (tpHHSJD == tpHHSJDFu->pHHSJDZuo) {
            tpHHSJDFu->pHHSJDZuo = tpHHSJDZuo;
        } else if (tpHHSJD == tpHHSJDFu->pHHSJDYou) {
            tpHHSJDFu->pHHSJDYou = tpHHSJDZuo;
        }
    }
    tpHHSJD->pHHSJDZuo = tpHHSJDZuoYou;
    if (tpHHSJDZuoYou != NULL) {
        tpHHSJDZuoYou->pHHSJDFu = tpHHSJD;
    }
}

void zhongXuBianLi(HHSJD *tpHHSJD) {
    if (tpHHSJD == NULL) {
        return;
    }
    zhongXuBianLi(tpHHSJD->pHHSJDZuo);
    printf("%d,", tpHHSJD->iShuZhi);
    zhongXuBianLi(tpHHSJD->pHHSJDYou);
}

void shanChuJieDian(HHSJD **tppHHSJDGen, int iShanChuZhi) {
    HHSJD *tpHHSJD = NULL;
    // 要删除的结点
    HHSJD *pHHSJDDel = NULL;
    // 兄弟结点
    HHSJD *tpHHSJDXiong = NULL;

    tpHHSJD = *tppHHSJDGen;
    // 找到要删除的结点
    while (tpHHSJD != NULL) {
        if (iShanChuZhi < tpHHSJD->iShuZhi) {
            tpHHSJD = tpHHSJD->pHHSJDZuo;
        } else if (iShanChuZhi > tpHHSJD->iShuZhi) {
            tpHHSJD = tpHHSJD->pHHSJDYou;
        } else {
            pHHSJDDel = tpHHSJD;
            break;
        }
    }
    if (pHHSJDDel != NULL) {
        // 能找到要删除的结点
        if (pHHSJDDel->pHHSJDZuo == NULL || pHHSJDDel->pHHSJDYou == NULL) {
            // 情况1：要删除的结点只有一个子树
            // 这种情况要删除的结点一定是黑色的，子树的根节点一定是红色的
            // 直接把子树接上来，并把子树的根节点改黑色
            if (pHHSJDDel->pHHSJDZuo == NULL) {
                // 左子树为空，把右子树接上来
                pHHSJDDel->pHHSJDYou->cYanSe = 'h';
                if (pHHSJDDel->pHHSJDFu->pHHSJDZuo == pHHSJDDel) {
                    pHHSJDDel->pHHSJDFu->pHHSJDZuo = pHHSJDDel->pHHSJDYou;
                } else {
                    pHHSJDDel->pHHSJDFu->pHHSJDYou = pHHSJDDel->pHHSJDYou;
                }
            } else {
                // 右子树为空，把左子树接上来
                pHHSJDDel->pHHSJDZuo->cYanSe = 'h';
                if (pHHSJDDel->pHHSJDFu->pHHSJDZuo == pHHSJDDel) {
                    pHHSJDDel->pHHSJDFu->pHHSJDZuo = pHHSJDDel->pHHSJDZuo;
                } else {
                    pHHSJDDel->pHHSJDFu->pHHSJDYou = pHHSJDDel->pHHSJDZuo;
                }
            }
        } else {
            // 到要删除的结点的左子树和右子树都存在
        }
        free(pHHSJDDel);
    }
}