#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*#####Trie树(字典树)#####*/

// 字符集数量，这个例子简化了数据规模，只考虑26个小写字母
#define ZI_FU_JI_SHU 26
// 模式串长度
#define MO_SHI_CHUAN_LEN 128

extern void chaRuJieDian();

extern int chaXunZiFuChuan();

// Trie树结点
typedef struct TrieJieDian {
    // 结点字符
    char cZiFu;
    // 是否是模式串结尾
    int ibJieWei;
    // 每个Trie树结点有26个子树
    struct TrieJieDian *tjdarrpZi[ZI_FU_JI_SHU];
} TJD;

int main() {
    // 根结点
    TJD *pTJDGen = (TJD *)malloc(sizeof(TJD));
    char sarr2MoShi[][MO_SHI_CHUAN_LEN] = {"black", "white", "gray",
                                           "blacl", "blacm", "whitff", "whitfg"};
    int isarr2MoShiLen = 7;
    char sChaXun1[] = "blaccwhitergrayy";
    int iSChaXun1Len = strlen(sChaXun1);

    // 初始化
    pTJDGen->cZiFu = '\0';
    pTJDGen->ibJieWei = 0;
    for (int ii = 0; ii < ZI_FU_JI_SHU; ++ii) {
        pTJDGen->tjdarrpZi[ii] = NULL;
    }
    // 依次向字典树中添加模式串
    for (int ii = 0; ii < isarr2MoShiLen; ii++) {
        for (int ij = 0; ij < strlen(sarr2MoShi[ii]); ij++) {
            chaRuJieDian(pTJDGen, sarr2MoShi[ii]);
        }
    }
    // 检查字符串中是否存在匹配上的模式串
    for (int ii = 0; ii < iSChaXun1Len; ++ii) {
        int iPiPeiLen = chaXunZiFuChuan(pTJDGen, sChaXun1, ii, iSChaXun1Len);
        if (iPiPeiLen > 0) {
            printf("%s,start=%d,len=%d\n", sChaXun1, ii, iPiPeiLen);
        };
    }
}

void chaRuJieDian(TJD *pTJDGen, char sMoShi[MO_SHI_CHUAN_LEN]) {
    TJD *tpTJD = pTJDGen, *tpTJDNew = NULL;
    int iZiFuIndex = 0, ii = 0;

    while (sMoShi[ii] != '\0') {
        // 计算字母的下标
        iZiFuIndex = (int)(tolower(sMoShi[ii]) - 'a');
        if (tpTJD->tjdarrpZi[iZiFuIndex] == NULL) {
            // 字典树中不存在前缀，就新构造一个结点
            tpTJDNew = (TJD *)malloc(sizeof(TJD));
            tpTJDNew->cZiFu = sMoShi[ii];
            tpTJDNew->ibJieWei = 0;
            for (int ij = 0; ij < ZI_FU_JI_SHU; ++ij) {
                tpTJDNew->tjdarrpZi[ij] = NULL;
            }
            // 把新的结点添加到字典树中
            tpTJD->tjdarrpZi[iZiFuIndex] = tpTJDNew;
        }
        // 遍历指针移动到当前结点
        tpTJD = tpTJD->tjdarrpZi[iZiFuIndex];
        ++ii;
    }
    // 最后一个结点标记为模式串结束结点
    tpTJD->ibJieWei = 1;
}

int chaXunZiFuChuan(TJD *pTJDGen, char *psMoShi, int iKaiShiIndex, int iSChaXun1Len) {
    TJD *tpTJD = pTJDGen;
    int iZiFuIndex = 0, iPiPeiLen = 0;

    for (int ii = iKaiShiIndex; ii < iSChaXun1Len; ++ii) {
        // 计算字母的下标
        iZiFuIndex = (int)(tolower(psMoShi[ii]) - 'a');
        if (tpTJD->tjdarrpZi[iZiFuIndex] == NULL) {
            // 如果不匹配就结束匹配
            break;
        }
        // 遍历指针移动到当前结点
        tpTJD = tpTJD->tjdarrpZi[iZiFuIndex];
        ++iPiPeiLen;
    }
    if (tpTJD->ibJieWei == 1) {
        // 如果当前结点是模式串结尾
        return iPiPeiLen;
    } else {
        return 0;
    }
}