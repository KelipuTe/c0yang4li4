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
    // 结点黑深度，下往上依次增加，最下层叶子结点的黑深度约定为0。
    int iJieDianHeiShenDu;
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
// 删除节点
extern void shanChuJieDian();
// 中序遍历
extern void zhongXuBianLi(HHSJD *);

int main() {
    // 根节点指针
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
        *tppHHSJD = (HHSJD *)malloc(sizeof(HHSJD));
        (*tppHHSJD)->iShuZhi = iChaRuZhi;
        (*tppHHSJD)->pHHSJDZuo = NULL;
        (*tppHHSJD)->pHHSJDYou = NULL;
        (*tppHHSJD)->pHHSJDFu = NULL;
        (*tppHHSJD)->iJieDianHeiShenDu = 1;
        (*tppHHSJD)->cYanSe = 'h';
    } else {
        if (iChaRuZhi < (*tppHHSJD)->iShuZhi) {
            if ((*tppHHSJD)->pHHSJDZuo != NULL) {
                chaRuJieDian(&((*tppHHSJD)->pHHSJDZuo), iChaRuZhi, tppHHSJDGen);
            } else {
                (*tppHHSJD)->pHHSJDZuo = (HHSJD *)malloc(sizeof(HHSJD));
                (*tppHHSJD)->pHHSJDZuo->iShuZhi = iChaRuZhi;
                (*tppHHSJD)->pHHSJDZuo->pHHSJDZuo = NULL;
                (*tppHHSJD)->pHHSJDZuo->pHHSJDYou = NULL;
                (*tppHHSJD)->pHHSJDZuo->pHHSJDFu = *tppHHSJD;
                (*tppHHSJD)->pHHSJDZuo->iJieDianHeiShenDu = 1;
                (*tppHHSJD)->pHHSJDZuo->cYanSe = 'r';
                tiaoZheng((*tppHHSJD)->pHHSJDZuo, tppHHSJDGen);
            }
        } else if (iChaRuZhi > (*tppHHSJD)->iShuZhi) {
            if ((*tppHHSJD)->pHHSJDYou != NULL) {
                chaRuJieDian(&((*tppHHSJD)->pHHSJDYou), iChaRuZhi, tppHHSJDGen);
            } else {
                (*tppHHSJD)->pHHSJDYou = (HHSJD *)malloc(sizeof(HHSJD));
                (*tppHHSJD)->pHHSJDYou->iShuZhi = iChaRuZhi;
                (*tppHHSJD)->pHHSJDYou->pHHSJDZuo = NULL;
                (*tppHHSJD)->pHHSJDYou->pHHSJDYou = NULL;
                (*tppHHSJD)->pHHSJDYou->pHHSJDFu = *tppHHSJD;
                (*tppHHSJD)->pHHSJDYou->iJieDianHeiShenDu = 1;
                (*tppHHSJD)->pHHSJDYou->cYanSe = 'r';
                tiaoZheng((*tppHHSJD)->pHHSJDYou, tppHHSJDGen);
            }
        } else {
            // 要插入的值已经存在
        }
    }
}

void tiaoZheng(HHSJD *tpHHSJD, HHSJD **tppHHSJDGen) {
    // 叔叔结点
    HHSJD *tpHHSJDShu = NULL;

    while (tpHHSJD != (*tppHHSJDGen) && tpHHSJD->pHHSJDFu->cYanSe == 'r') {
        // 当父节点为红色时才需要调整
        if (tpHHSJD->pHHSJDFu == tpHHSJD->pHHSJDFu->pHHSJDFu->pHHSJDZuo) {
            // 父结点是祖父节点的左孩子
            tpHHSJDShu = tpHHSJD->pHHSJDFu->pHHSJDFu->pHHSJDYou;
            if (tpHHSJDShu != NULL && tpHHSJDShu->cYanSe == 'r') {
                // 叔叔结点是红色，父结点和叔叔结点改黑色，祖父结点改红色
                tpHHSJD->pHHSJDFu->cYanSe = 'h';
                tpHHSJDShu->cYanSe = 'h';
                tpHHSJD->pHHSJDFu->pHHSJDFu->cYanSe = 'r';
                // 继续判断祖父节点
                tpHHSJD = tpHHSJD->pHHSJDFu->pHHSJDFu;
            } else {
                // 叔叔结点是黑色，叔叔结点不存在是也认为是黑色的
                if (tpHHSJD == tpHHSJD->pHHSJDFu->pHHSJDYou) {
                    // 自己是父结点的右孩子，父结点左旋，继续判断父节点
                    tpHHSJD = tpHHSJD->pHHSJDFu;
                    zuoXuan(tpHHSJD, tppHHSJDGen);
                } else {
                    // 自己是父结点的左孩子，父结点改黑色，祖父节点改红色，祖父节点右旋
                    tpHHSJD->pHHSJDFu->cYanSe = 'h';
                    tpHHSJD->pHHSJDFu->pHHSJDFu->cYanSe = 'r';
                    youXuan(tpHHSJD->pHHSJDFu->pHHSJDFu, tppHHSJDGen);
                }
            }
        } else {
            // 父结点是祖父节点的右孩子
            tpHHSJDShu = tpHHSJD->pHHSJDFu->pHHSJDFu->pHHSJDZuo;
            if (tpHHSJDShu != NULL && tpHHSJDShu->cYanSe == 'r') {
                // 叔叔结点是红色，父结点和叔叔结点改黑色，祖父结点改红色
                tpHHSJD->pHHSJDFu->cYanSe = 'h';
                tpHHSJDShu->cYanSe = 'h';
                tpHHSJD->pHHSJDFu->pHHSJDFu->cYanSe = 'r';
                // 继续判断祖父节点
                tpHHSJD = tpHHSJD->pHHSJDFu->pHHSJDFu;
            } else {
                // 叔叔结点是黑色，叔叔结点不存在是也认为是黑色的
                if (tpHHSJD == tpHHSJD->pHHSJDFu->pHHSJDZuo) {
                    // 自己是父结点的右孩子，父结点右旋，继续判断父节点
                    tpHHSJD = tpHHSJD->pHHSJDFu;
                    youXuan(tpHHSJD, tppHHSJDGen);
                } else {
                    // 自己是父结点的左孩子，父结点改黑色，祖父节点改红色，祖父节点左旋
                    tpHHSJD->pHHSJDFu->cYanSe = 'h';
                    tpHHSJD->pHHSJDFu->pHHSJDFu->cYanSe = 'r';
                    zuoXuan(tpHHSJD->pHHSJDFu->pHHSJDFu, tppHHSJDGen);
                }
            }
        }
    }
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
    HHSJD *pHHSJDDel = NULL;
    HHSJD *tpHHSJD = NULL;
    HHSJD *tpHHSJDXiong = NULL;

    tpHHSJD = *tppHHSJDGen;
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
        if (pHHSJDDel->pHHSJDZuo == NULL) {
            // 如果要删除的结点左子树为空，直接把右子树接上来
            if (pHHSJDDel->pHHSJDFu->pHHSJDZuo == pHHSJDDel) {
                pHHSJDDel->pHHSJDFu->pHHSJDZuo = pHHSJDDel->pHHSJDYou;
            } else if (pHHSJDDel->pHHSJDFu->pHHSJDYou == pHHSJDDel) {
                pHHSJDDel->pHHSJDFu->pHHSJDYou = pHHSJDDel->pHHSJDYou;
            }
        } else if (pHHSJDDel->pHHSJDYou == NULL) {
            // 如果要删除的结点左子树为空，直接把左子树接上来
            if (pHHSJDDel->pHHSJDFu->pHHSJDZuo == pHHSJDDel) {
                pHHSJDDel->pHHSJDFu->pHHSJDZuo = pHHSJDDel->pHHSJDZuo;
            } else if (pHHSJDDel->pHHSJDFu->pHHSJDYou == pHHSJDDel) {
                pHHSJDDel->pHHSJDFu->pHHSJDYou = pHHSJDDel->pHHSJDZuo;
            }
        } else {
            // 如果目标结点的左子树和右子树都存在
            // 可以从左子树中找到结点值最大的结点替代被删除的结点
            // 同理，从右子树中找到结点值最小的结点也是可行的
            pHHSJDDel->pHHSJDFu = pHHSJDDel;
            tpHHSJD = pHHSJDDel->pHHSJDZuo;
            while (tpHHSJD->pHHSJDYou != NULL) {
                pHHSJDDel->pHHSJDFu = tpHHSJD;
                tpHHSJD = tpHHSJD->pHHSJDYou;
            }
            // 直接把结点值最大的结点的结点值赋值到要删除的结点上，颜色不变
            pHHSJDDel->iShuZhi = tpHHSJD->iShuZhi;
            if (pHHSJDDel->pHHSJDFu != pHHSJDDel) {
                // 如果替代结点的前驱结点不是删除结点的位置
                // 则删除结点左结点有右结点，需要考虑该右结点的左子树
                pHHSJDDel->pHHSJDFu->pHHSJDYou = tpHHSJD->pHHSJDZuo;
            } else {
                // 如果替代结点的前驱结点就是删除结点的位置
                // 则删除结点左结点没有右结点，直接把该左结点的左子树接过来
                pHHSJDDel->pHHSJDFu->pHHSJDZuo = tpHHSJD->pHHSJDZuo;
            }
            pHHSJDDel = tpHHSJD;
        }
        // 如果删除的结点颜色是红色，可以直接删除，黑色需要额外处理
        if (pHHSJDDel->cYanSe == 'h') {
            tpHHSJD = pHHSJDDel;
            while (tpHHSJD != *tppHHSJDGen && tpHHSJD->cYanSe == 'h') {
                if (tpHHSJD == tpHHSJD->pHHSJDFu->pHHSJDZuo) {
                    tpHHSJDXiong = tpHHSJD->pHHSJDFu->pHHSJDYou;
                    if (tpHHSJDXiong->cYanSe = 'r') {
                        // 兄弟节点是红色的
                        tpHHSJDXiong->cYanSe = 'h';
                        tpHHSJDXiong->pHHSJDFu->cYanSe = 'r';
                        zuoXuan(tpHHSJD->pHHSJDFu, tppHHSJDGen);
                        tpHHSJDXiong = tpHHSJD->pHHSJDFu->pHHSJDYou;
                    }
                    if (tpHHSJDXiong->pHHSJDZuo->cYanSe == 'h' && tpHHSJDXiong->pHHSJDYou->cYanSe == 'h') {
                        tpHHSJDXiong->cYanSe = 'r';
                        tpHHSJD = tpHHSJD->pHHSJDFu;
                    }
                    if (tpHHSJDXiong->pHHSJDZuo->cYanSe == 'r' && tpHHSJDXiong->pHHSJDYou->cYanSe == 'h') {
                        tpHHSJDXiong->pHHSJDZuo->cYanSe = 'h';
                        tpHHSJDXiong->cYanSe = 'r';
                        youXuan(tpHHSJDXiong, tppHHSJDGen);
                        tpHHSJDXiong = tpHHSJD->pHHSJDFu->pHHSJDYou;
                    }
                    if (tpHHSJDXiong->pHHSJDYou->cYanSe = 'r') {
                        tpHHSJDXiong->cYanSe = tpHHSJD->pHHSJDFu->cYanSe;
                        tpHHSJD->pHHSJDFu->cYanSe = 'h';
                        tpHHSJDXiong->pHHSJDYou = 'h';
                        zuoXuan(tpHHSJD->pHHSJDFu, tppHHSJDGen);
                        tpHHSJD = *tppHHSJDGen;
                    }
                } else {
                    tpHHSJDXiong = tpHHSJD->pHHSJDFu->pHHSJDZuo;
                }
            }
            tpHHSJD->cYanSe = 'h';
        }
        free(pHHSJDDel);
    }
}