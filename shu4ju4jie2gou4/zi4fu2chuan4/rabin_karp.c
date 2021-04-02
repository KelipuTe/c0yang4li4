#include <stdio.h>
#include <string.h>

/*#####Rabin-Karp算法#####*/

// 哈希函数，计算字符串哈希值
extern int haXiHanShu();

int main() {
    // 匹配串，模式串
    char sPiPei[] = "abcadabcabdababdabcab", sMoShi[] = "dabcab";
    // 匹配串长度，模式串长度
    int iSPiPeiLen = 0, iSMoShiLen = 0;
    // 匹配串哈希值，模式串哈希值，
    int iHaXiZhu = 0, iHaXiZi = 0;

    iSPiPeiLen = strlen(sPiPei);
    iSMoShiLen = strlen(sMoShi);
    // 计算子串的哈希值
    iHaXiZi = haXiHanShu(sMoShi, 0, iSMoShiLen);
    // 依次截取匹配串中长度和模式串相同的子串，计算哈希值并进行比较
    // 注意这里是小于等于，处理一样长或者正好是后缀的情况
    for (int ii = 0; ii <= iSPiPeiLen - iSMoShiLen; ii++) {
        iHaXiZhu = haXiHanShu(sPiPei, ii, ii + iSMoShiLen);
        if (iHaXiZhu == iHaXiZi) {
            // 如果哈希值相同，再校验一次，确认字符串是否相同
            int ibCheck = 1;
            for (int ij = 0; ij < iSMoShiLen; ij++) {
                if (sPiPei[ii + ij] != sMoShi[ij]) {
                    ibCheck = 0;
                }
            }
            if (ibCheck == 1) {
                // 匹配完成，如果只找一个，那么这里可以结束了
                printf("%d\n", ii);
            }
        }
    }
}

int haXiHanShu(char *psKey, int iStart, int iEnd) {
    int iHaXiZhi = 0;

    {
        int ii = iStart, ij = 0;
        while (ii < iEnd) {
            iHaXiZhi += (int)psKey[ii] * (ij + 1);
            ii++;
            ij++;
        }
    }

    return iHaXiZhi;
}