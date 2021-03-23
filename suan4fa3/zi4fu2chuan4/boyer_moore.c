#include <math.h>
#include <stdio.h>
#include <string.h>

/*#####Boyer-Moore算法#####*/

// 字符集数量
#define ZI_FU_JI_SHU 256
// 模式串长度
#define MO_SHI_CHUAN_LEN 128

int main() {
    // 匹配串，模式串
    char sPiPei[] = "abcacabdabcabab", sMoSHi[] = "dabcab";
    // 匹配串长度，模式串长度
    int iSPiPeiLen = 0, iSMoSHiLen = 0;
    // 坏字符
    int iarrHuaiZiFu[256] = {0};
    // 好后缀
    // 模式串后缀在模式串前面再次出现的位置，能和后缀匹配的前缀的长度
    int iarrHaoHouZhui[MO_SHI_CHUAN_LEN] = {0}, ibarrHaoQianZhui[MO_SHI_CHUAN_LEN] = {0};

    iSPiPeiLen = strlen(sPiPei);
    iSMoSHiLen = strlen(sMoSHi);

    // 找到每个字符在模式串中最后出现的位置
    for (int ii = 0; ii < iSMoSHiLen; ii++) {
        iarrHuaiZiFu[(int)sMoSHi[ii]] = ii;
    }
    // 处理好后缀的两个数组
    // 初始化
    for (int ii = 0; ii < MO_SHI_CHUAN_LEN; ii++) {
        iarrHaoHouZhui[ii] = -1;
        ibarrHaoQianZhui[ii] = 0;
    }
    for (int ii = 0; ii < iSMoSHiLen - 1; ii++) {
        // 比较的是从0到ii下标位置的前缀子串，所以长度-1
        int ij = ii, ik = 0;
        iarrHaoHouZhui[ik] = -1;
        ibarrHaoQianZhui[ii] = 0;
        // 求模式串从0到ii下标位置的前缀子串和整个模式串的公共后缀
        while (ij >= 0 && sMoSHi[ij] == sMoSHi[iSMoSHiLen - 1 - ik]) {
            ik++;
            iarrHaoHouZhui[ik] = ij;
            ij--;
        }
        if (ij < 0) {
            // j<0证明，模式串从0到ii下标位置的前缀子串，是模式串的后缀之一
            ibarrHaoQianZhui[ii] = 1;
        }
    }
    {
        int ii = 0;
        while (ii <= iSPiPeiLen - iSMoSHiLen) {
            int ij = 0;
            // 从末尾开始比较
            for (ij = iSMoSHiLen - 1; ij >= 0; ij--) {
                if (sPiPei[ii + ij] != sMoSHi[ij]) {
                    break;
                }
            }
            if (ij < 0) {
                // 匹配完成
                printf("%d\n", ii);
                ii++;
                continue;
            }
            // 如果没匹配到，那么ij就是坏字符的位置
            int ia = ij - iarrHuaiZiFu[(int)sPiPei[ii + ij]];
            int ib = 0;
            if (ij < iSMoSHiLen - 1) {
                // ij往前移动了，证明后缀有一部分匹配上了
                // 好后缀的长度
                int ik = iSMoSHiLen - 1 - ij;
                if (iarrHaoHouZhui[ik] != -1) {
                    // 看看这部分后缀在模式串前面有没有
                    ib = ij - iarrHaoHouZhui[ik] + 1;
                } else {
                    ib = iSMoSHiLen;
                    // 看看这部分后缀里有没有满足条件的前缀
                    for (int il = ij + 2; il <= iSMoSHiLen - 1; il++) {
                        if (ibarrHaoQianZhui[iSMoSHiLen - il] == 1) {
                            ib = il;
                        }
                    }
                }
            }
            ii = ii + fmax(ia, ib);
        }
    }
}