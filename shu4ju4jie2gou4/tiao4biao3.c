#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

/*#####跳表#####*/

// 跳表层数，最下面一层索引存储了全部的数据
#define BIAO_CENG_SHU 3

// 跳表结点
typedef struct TiaoBiaoJieDian {
    // 数值
    int iShuZhi;
    // 这个结点的最大索引层数
    int iCengShu;
    // 这个结点在各个索引层的下一个结点
    struct TiaoBiaoJieDian *tbjdarrpNext[BIAO_CENG_SHU];
} TBJD;

extern void chaRuJieDian();
extern int suiJiCengShu();

int main() {
    TBJD TBJDTou = (TBJD *)malloc(sizeof(TBJD));

    // for (int ii = 0; ii < 10; ii++) {
    //     printf("%d\n", suiJiCengShu());
    // }
    chaRuJieDian(&TBJDTou, 10);

    return 0;
}

void chaRuJieDian(TBJD *pTBJDTou, int iShuZhi) {
    TBJD *tpTBJD = (TBJD *)malloc(sizeof(TBJD));
    tpTBJD->iShuZhi = iShuZhi;
    tpTBJD->iCengShu = suiJiCengShu();
}

int suiJiCengShu() {
    int iCengShu = 0;

    srand((unsigned)time(NULL));
    for (int ii = 0; ii < BIAO_CENG_SHU; ii++) {
        if ((rand() % 4) > 1) {
            iCengShu++;
        }
        Sleep(200);
    }

    return iCengShu;
}