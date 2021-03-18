#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*#####散列表#####*/

// 散列表最大长度
#define BIAO_CHANG_MAX 20
// 散列函数
extern int sanLieHanShu();

// 链表结点
typedef struct LianBiaoJieDian {
    // 键值
    char sKey[10];
    // 下一个结点的指针
    struct LianBiaoJieDian *pLBJDNext;
} LBJD;

// 输出链表
extern void shuChuLianBiao();
// 添加结点
extern void tianJiaXiang();
// 移除指定结点
extern void yiChuXiang();

int main() {
    // 散列表长度
    int iSanLieBiaoChang = 0;
    // 散列因子=散列表长/
    float fSanLieYinZi = 0;
    // 散列表哈希槽指针
    LBJD *pSanLieBiao[BIAO_CHANG_MAX] = {NULL};

    char sarr[][10] = {"aaa", "bbb", "ccc"};
    int iSArrLen = 3;
    int tiSanLieZhi = 0;
    for (int ii = 0; ii < iSArrLen; ii++) {
        tiSanLieZhi = sanLieHanShu(sarr[ii]);
        tianJiaXiang(&pSanLieBiao[tiSanLieZhi], sarr[ii]);
    }

    char sStr[] = "bbb";
    tiSanLieZhi = sanLieHanShu(sStr);
    LBJD *tpLBJD = pSanLieBiao[tiSanLieZhi];
    while (tpLBJD != NULL) {
        int ii = 0;
        int ibCheck = 0;
        while (sStr[ii] != '\0') {
            if (sStr[ii] != tpLBJD->sKey[ii]) {
                ibCheck = 1;
            }
            ii++;
        }
        if (ibCheck == 0) {
            printf("find:%s", tpLBJD->sKey);
            break;
        }
        tpLBJD = tpLBJD->pLBJDNext;
    }

    return 0;
}

int sanLieHanShu(char *psKey) {
    // 散列值
    int iSanLieZhi = 0, ii = 0;
    // 散列值=字符acsii码值*字符位数
    while (psKey[ii] != '\0') {
        iSanLieZhi += (int)psKey[ii] * (ii + 1);
        ii++;
    }
    // 散列值对散列表最大长度取模，映射到散列表坐标
    return iSanLieZhi % BIAO_CHANG_MAX;
}

void shuChuLianBiao(LBJD *pLBJDTou) {
    LBJD *tpLBJD = pLBJDTou;

    printf("lian4biao3:");
    if (pLBJDTou != NULL) {
        // 注意空表
        while (tpLBJD != NULL) {
            printf("12%s,", tpLBJD->sKey);
            tpLBJD = tpLBJD->pLBJDNext;
        }
    }
    printf("\n");
}

void tianJiaXiang(LBJD **ppLBJDTou, char *psKey) {
    LBJD *tpLBJDNew = (LBJD *)malloc(sizeof(LBJD)), *tpLBJD = NULL;
    memset(tpLBJDNew->sKey, 0, sizeof(char) * 10);

    int ii = 0;
    while (psKey[ii] != '\0') {
        tpLBJDNew->sKey[ii] = psKey[ii];
        ii++;
    }
    tpLBJDNew->pLBJDNext = NULL;
    if (*ppLBJDTou == NULL) {
        // 链表为空
        *ppLBJDTou = tpLBJDNew;
    } else {
        // 链表不为空，则把结点连接到链表尾部
        tpLBJD = *ppLBJDTou;
        while (tpLBJD->pLBJDNext != NULL) {
            tpLBJD = tpLBJD->pLBJDNext;
        }
        tpLBJD->pLBJDNext = tpLBJDNew;
    }
}

// void yiChuXiang(LBJD **ppLBJDTou, LBJD **ppLBJDWei, int iShuZhi) {
//     // 当前结点，上一个结点
//     LBJD *tpLBJDNow = *ppLBJDTou, *tpLBJDLast = *ppLBJDTou;

//     if (*ppLBJDTou != NULL) {
//         while (tpLBJDNow != NULL) {
//             if (tpLBJDNow->iShuZhi == iShuZhi) {
//                 if (tpLBJDNow == *ppLBJDTou) {
//                     // 刚好是头
//                     *ppLBJDTou = tpLBJDNow->pLBJDNext;
//                     free(tpLBJDNow);
//                     tpLBJDNow = *ppLBJDTou;
//                 } else if (tpLBJDNow == *ppLBJDWei) {
//                     // 刚好是尾
//                     tpLBJDLast->pLBJDNext = NULL;
//                     *ppLBJDWei = tpLBJDLast;
//                     free(tpLBJDNow);
//                     tpLBJDNow = NULL;
//                 } else {
//                     // 连接当前结点的前一个结点和后一个结点
//                     tpLBJDLast->pLBJDNext = tpLBJDNow->pLBJDNext;
//                     free(tpLBJDNow);
//                     tpLBJDNow = tpLBJDLast->pLBJDNext;
//                 }
//             } else {
//                 // 指针后移继续寻找
//                 tpLBJDLast = tpLBJDNow;
//                 tpLBJDNow = tpLBJDNow->pLBJDNext;
//             }
//         }
//     }
// }