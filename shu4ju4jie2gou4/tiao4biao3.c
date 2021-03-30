#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

/*#####跳表#####*/

// 跳表层数，最下面一层索引存储了全部的数据
#define BIAO_CENG_SHU 5

// 跳表结点
typedef struct TiaoBiaoJieDian {
    // 数值
    int iShuZhi;
    // 这个结点的最大索引层数
    int iCengShu;
    // 这个结点在各个索引层的下一个结点
    struct TiaoBiaoJieDian *tbjdarrpNext[BIAO_CENG_SHU];
} TBJD;

// 插入结点
extern void chaRuJieDian();
// 随机层数
extern int suiJiCengShu();
// 输出跳表
extern void shuChuTiaoBiao();
// 移除结点
extern void yiChuJieDian();

void arrToString(int *iarr, int iArrLen) {
    for (int ii = 0; ii < iArrLen; ii++) {
        printf("%d,", iarr[ii]);
    }
    printf("\n");
}

int main() {
    // 头结点
    TBJD *pTBJDTou = (TBJD *)malloc(sizeof(TBJD));
    int iarr[50] = {61, 51, 81, 90, 89, 90, 19, 45, 80, 28, 71, 92, 9, 58, 68, 78, 9, 19, 89, 20, 4, 73, 25, 76, 87, 72, 60, 17, 2, 83, 82, 55, 35, 2, 37, 19, 93, 21, 8, 24, 50, 69, 75, 50, 39, 9, 37, 42, 5, 96};
    int iArrLen = 50;

    pTBJDTou->iShuZhi = -1;
    pTBJDTou->iCengShu = -1;
    for (int ii = 0; ii < BIAO_CENG_SHU; ii++) {
        pTBJDTou->tbjdarrpNext[ii] = NULL;
    }

    // srand(time(NULL));
    // for (int ii = 0; ii < 50; ii++) {
    //     iarr[ii] = (rand() % 99) + 1;
    // }
    // printf("arrayToString:");
    // arrToString(&iarr, iArrLen);

    for (int ii = 0; ii < 50; ii++) {
        chaRuJieDian(pTBJDTou, iarr[ii]);
    }

    shuChuTiaoBiao(pTBJDTou);

    yiChuJieDian(pTBJDTou, iarr[28]);
    yiChuJieDian(pTBJDTou, iarr[10]);
    yiChuJieDian(pTBJDTou, iarr[20]);

    shuChuTiaoBiao(pTBJDTou);

    return 0;
}

void chaRuJieDian(TBJD *pTBJDTou, int iShuZhi) {
    // 本次插入的新结点
    TBJD *tpTBJDNew = NULL, *tpTBJD = NULL;
    // 每个索引行需要更新的结点
    TBJD *ttbjdarrpUpdate[BIAO_CENG_SHU] = {NULL};

    // 初始化每层要更新的结点为头结点
    for (int ii = 0; ii < BIAO_CENG_SHU; ii++) {
        ttbjdarrpUpdate[ii] = pTBJDTou;
    }

    // 找到插入新结点时，所有需要更新的位置
    tpTBJD = pTBJDTou;
    for (int ii = BIAO_CENG_SHU - 1; ii >= 0; ii--) {
        // 从最高的索引层开始遍历
        // 找到这层索引中，比目标值小的最大的结点
        while (tpTBJD->tbjdarrpNext[ii] != NULL && tpTBJD->tbjdarrpNext[ii]->iShuZhi < iShuZhi) {
            tpTBJD = tpTBJD->tbjdarrpNext[ii];
        }
        if (tpTBJD->tbjdarrpNext[ii] != NULL && tpTBJD->tbjdarrpNext[ii]->iShuZhi == iShuZhi) {
            // 发现表里已经存在要插入的结点，直接返回
            printf("jump-%d,", iShuZhi);
            return;
        }
        // 把这个结点保存下来
        ttbjdarrpUpdate[ii] = tpTBJD;
        // 进入下面一层的遍历
    }

    // 初始化新结点
    tpTBJDNew = (TBJD *)malloc(sizeof(TBJD));
    tpTBJDNew->iShuZhi = iShuZhi;
    tpTBJDNew->iCengShu = suiJiCengShu();
    for (int ii = 0; ii < BIAO_CENG_SHU; ii++) {
        tpTBJDNew->tbjdarrpNext[ii] = NULL;
    }
    printf("add-%d,", iShuZhi);
    // 把新结点接到各层索引中去
    for (int ii = tpTBJDNew->iCengShu - 1; ii >= 0; ii--) {
        tpTBJDNew->tbjdarrpNext[ii] = ttbjdarrpUpdate[ii]->tbjdarrpNext[ii];
        ttbjdarrpUpdate[ii]->tbjdarrpNext[ii] = tpTBJDNew;
    }
}

int suiJiCengShu() {
    int iCengShu = 0;

    // rand函数是基于时间的伪随机函数，sleep是为了将执行时间错开
    for (int ii = 0; ii < BIAO_CENG_SHU; ii++) {
        if ((rand() % 4) > 1) {
            iCengShu++;
        }
        Sleep(200);
    }

    return iCengShu;
}

void shuChuTiaoBiao(TBJD *pTBJDTou) {
    TBJD *tpTBJD = NULL;

    printf("\n");
    for (int ii = BIAO_CENG_SHU - 1; ii >= 0; ii--) {
        printf("cengshu-%d:", ii);
        tpTBJD = pTBJDTou;
        while (tpTBJD->tbjdarrpNext[ii] != NULL) {
            printf("%d,", tpTBJD->iShuZhi);
            tpTBJD = tpTBJD->tbjdarrpNext[ii];
        }
        printf("%d,", tpTBJD->iShuZhi);
        printf("\n");
    }
}

void yiChuJieDian(TBJD *pTBJDTou, int iShuZhi) {
    TBJD *tpTBJD = NULL;
    // 每个索引行需要更新的结点
    TBJD *ttbjdarrpUpdate[BIAO_CENG_SHU] = {NULL};

    for (int ii = 0; ii < BIAO_CENG_SHU; ii++) {
        ttbjdarrpUpdate[ii] = pTBJDTou;
    }
    // 找到插入新结点时，所有需要更新的位置
    tpTBJD = pTBJDTou;
    for (int ii = BIAO_CENG_SHU - 1; ii >= 0; ii--) {
        // 从最高的索引层开始遍历
        // 找到这层索引中，比目标值小的最大的结点
        while (tpTBJD->tbjdarrpNext[ii] != NULL && tpTBJD->tbjdarrpNext[ii]->iShuZhi < iShuZhi) {
            tpTBJD = tpTBJD->tbjdarrpNext[ii];
        }
        ttbjdarrpUpdate[ii] = tpTBJD;
        // 进入下面一层的遍历
    }
    // 循环结束之后tpTBJD指向要删除结点的前一个结点，判断一下后面那个结点是不是要删除的结点
    if (tpTBJD->tbjdarrpNext[0] != NULL && tpTBJD->tbjdarrpNext[0]->iShuZhi == iShuZhi) {
        // 后面那个结点是删除的结点
        for (int ii = tpTBJD->tbjdarrpNext[0]->iCengShu - 1; ii >= 0; ii--) {
            // 获取一下结点的层数，删掉这个结点在每一个索引层的记录
            if (ttbjdarrpUpdate[ii]->tbjdarrpNext[ii] != NULL && ttbjdarrpUpdate[ii]->tbjdarrpNext[ii]->iShuZhi == iShuZhi) {
                ttbjdarrpUpdate[ii]->tbjdarrpNext[ii] = ttbjdarrpUpdate[ii]->tbjdarrpNext[ii]->tbjdarrpNext[ii];
            }
        }
        printf("delete-%d,", iShuZhi);
    }
}