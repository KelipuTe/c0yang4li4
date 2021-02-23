#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*#####leetcode67-二进制求和#####*/

char *addBinary(char *a, char *b) {
    int iStrALen = 0, iStrBLen = 0, iResIndex = 0;
    char *psRes = NULL;

    iStrALen = strlen(a);
    iStrBLen = strlen(b);
    if (iStrALen == 0) {
        return b;
    }
    if (iStrBLen == 0) {
        return a;
    }
    // 要多2位，一位用于最前面的进位，一位用于最后面的'\0'
    if (iStrALen > iStrBLen) {
        psRes = (char *)malloc(sizeof(char) * (iStrALen + 2));
        memset(psRes, 0, sizeof(char) * (iStrALen + 2));
        psRes[iStrALen + 1] = '\0';
        iResIndex = iStrALen;
    } else {
        psRes = (char *)malloc(sizeof(char) * (iStrBLen + 2));
        memset(psRes, 0, sizeof(char) * (iStrBLen + 2));
        psRes[iStrBLen + 1] = '\0';
        iResIndex = iStrBLen;
    }
    {
        int i = iStrALen, j = iStrBLen, ti = 0, tibJinWei = 0;
        // -48是因为字符串1的ascll码是49，(int)'1'=49
        while (i > 0 && j > 0) {
            ti = (int)a[i - 1] - 48 + (int)b[j - 1] - 48 + tibJinWei;
            if (ti == 3) {
                psRes[iResIndex] = '1';
                tibJinWei = 1;
            } else if (ti == 2) {
                psRes[iResIndex] = '0';
                tibJinWei = 1;
            } else {
                psRes[iResIndex] = (char)(ti + 48);
                tibJinWei = 0;
            }
            i--;
            j--;
            iResIndex--;
        }
        // 处理不一样长的部分
        while (i > 0) {
            ti = (int)a[i - 1] - 48 + tibJinWei;
            if (ti == 3) {
                psRes[iResIndex] = '1';
                tibJinWei = 1;
            } else if (ti == 2) {
                psRes[iResIndex] = '0';
                tibJinWei = 1;
            } else {
                psRes[iResIndex] = (char)(ti + 48);
                tibJinWei = 0;
            }
            i--;
            iResIndex--;
        }
        while (j > 0) {
            ti = (int)b[j - 1] - 48 + tibJinWei;
            if (ti == 3) {
                psRes[iResIndex] = '1';
                tibJinWei = 1;
            } else if (ti == 2) {
                psRes[iResIndex] = '0';
                tibJinWei = 1;
            } else {
                psRes[iResIndex] = (char)(ti + 48);
                tibJinWei = 0;
            }
            j--;
            iResIndex--;
        }
        // 处理第一位
        if (tibJinWei == 1) {
            psRes[iResIndex] = '1';
            return psRes;
        } else {
            return psRes + 1;
        }
    }
}

int main() {
    // char *sA = "1010";
    // char *sB = "1011";
    char *sA = "1";
    char *sB = "111";
    char *sRes = NULL;

    sRes = addBinary(sA, sB);
    printf("%s", sRes);
}