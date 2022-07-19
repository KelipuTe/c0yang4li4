#include <math.h>
#include <stdio.h>
#include <string.h>

/*#####Knuth-Morris-Pratt算法#####*/

// 模式串长度
#define MO_SHI_CHUAN_LEN 128

int main() {
    // 匹配串，模式串
    char sPiPei[] = "abcadaabababcabdabcababababcaa", sMoShi[] = "abababca";
    // 匹配串长度，模式串长度
    int iSPiPeiLen = 0, iSMoSHiLen = 0;

    int iarrNext[MO_SHI_CHUAN_LEN] = {0};

    iSPiPeiLen = strlen(sPiPei);
    iSMoSHiLen = strlen(sMoShi);

    iarrNext[0] = -1;
    int ii = 0, ij = -1;
    while (ii < iSMoSHiLen - 1) {
        if (ij == -1 || sMoShi[ii] == sMoShi[ij]) {
            ii++;
            ij++;
            iarrNext[ii] = ij;
        } else {
            ij = iarrNext[ij];
        }
    }

    ii = 0, ij = 0;
    while (ii < iSPiPeiLen && ij < iSMoSHiLen) {
        if (ij == -1 || sPiPei[ii] == sMoShi[ij]) {
            ii++;
            ij++;
        } else {
            ij = iarrNext[ij];
        }
    }
    if (ij == iSMoSHiLen) {
        printf("%d,", ii - ij);
    }
}