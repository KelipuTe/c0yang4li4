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
    char sPiPei[] = "abcadabcabdababdabcab", sMoShi[] = "dabcab";
    // 匹配串长度，模式串长度
    int iSPiPeiLen = 0, iSMoSHiLen = 0;
    // 坏字符规则
    int iarrHuaiZiFu[256] = {0};
    // 好后缀规则
    // 模式串后缀在模式串前面再次出现的位置，能和后缀匹配的前缀的长度
    int iarrHaoHouZhui[MO_SHI_CHUAN_LEN] = {0}, ibarrHaoQianZhui[MO_SHI_CHUAN_LEN] = {0};

    iSPiPeiLen = strlen(sPiPei);
    iSMoSHiLen = strlen(sMoShi);

    // 坏字符规则，找到每个字符在模式串中最后出现的位置
    for (int ii = 0; ii < iSMoSHiLen; ii++) {
        iarrHuaiZiFu[(int)sMoShi[ii]] = ii;
    }
    // 处理好后缀规则的两个数组
    // 初始化
    for (int ii = 0; ii < MO_SHI_CHUAN_LEN; ii++) {
        iarrHaoHouZhui[ii] = -1;
        ibarrHaoQianZhui[ii] = 0;
    }
    // 依次比较的是从0到ii下标位置的前缀子串，所以长度-1
    for (int ii = 0; ii < iSMoSHiLen - 1; ii++) {
        // ij，公共后缀长度
        int ij = ii, ik = 0;
        // 求模式串从0到ii下标位置的前缀子串和整个模式串的公共后缀
        while (ij >= 0 && sMoShi[ij] == sMoShi[iSMoSHiLen - 1 - ik]) {
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
        // 当匹配串的子串长度小于模式串时，就不需要在匹配了
        while (ii <= iSPiPeiLen - iSMoSHiLen) {
            int ij = 0;
            // BM算法从模式串的末尾开始比较
            for (ij = iSMoSHiLen - 1; ij >= 0; ij--) {
                if (sPiPei[ii + ij] != sMoShi[ij]) {
                    break;
                }
            }
            if (ij < 0) {
                // 匹配完成，如果只找一个，那么这里可以结束了
                printf("%d\n", ii);
                // 匹配位置后移，匹配下一处
                ii++;
            } else {
                // 如果没匹配完成，那么ij就是坏字符的位置
                // 确认坏字符规则以移动位数
                int ia = ij - iarrHuaiZiFu[(int)sPiPei[ii + ij]];
                // 确认好后缀规则的移动位数
                int ib = 0;
                if (ij < iSMoSHiLen - 1) {
                    // ij往前移动了，证明后缀有一部分匹配上了
                    // 完成匹配的后缀的长度
                    int ik = iSMoSHiLen - 1 - ij;
                    if (iarrHaoHouZhui[ik] != -1) {
                        // 如果这部分后缀在模式串前面存在，就把匹配串移动到相应的对齐的位置
                        ib = ij - iarrHaoHouZhui[ik] + 1;
                    } else {
                        // 如果找不到后缀，先认为要移动整个模式串的长度
                        // 然后判断完成匹配的后缀有没有和模式串的前缀重合
                        ib = iSMoSHiLen;
                        // 如果这部分后缀(后缀里的子后缀串也可以)，能匹配到满足条件的前缀，就把匹配串移动到相应的对齐的位置
                        for (int il = ij + 1; il <= iSMoSHiLen - 1; il++) {
                            if (ibarrHaoQianZhui[iSMoSHiLen - il] == 1) {
                                ib = il;
                            }
                        }
                    }
                }
                // 选移动位数大的那个
                ii = ii + fmax(ia, ib);
            }
        }
    }
}