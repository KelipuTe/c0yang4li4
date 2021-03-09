#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*#####leetcode6-Z字形变换#####*/

char *convert(char *s, int numRows) {
    int iSLen = strlen(s), iTime = (numRows - 1) * 2;
    char *psRes = malloc(sizeof(char) * (iSLen + 1));
    memset(psRes, 0, sizeof(char) * (iSLen + 1));
    int iSResNum = 0;

    if (numRows <= 1) {
        free(psRes);

        return s;
    }

    // 最上面一行
    for (int i = 0; i * iTime < iSLen; i++) {
        psRes[iSResNum++] = s[i * iTime];
    }
    // 中间都是两个一组
    for (int j = 1; j < numRows - 1; j++) {
        for (int i = 0; i * iTime < iSLen; i++) {
            if ((i * iTime) + j < iSLen) {
                psRes[iSResNum++] = s[(i * iTime) + j];
            }
            if ((i * iTime) + iTime - j < iSLen) {
                psRes[iSResNum++] = s[(i * iTime) + iTime - j];
            }
        }
    }
    // 最下面一行
    for (int i = 0; i * iTime < iSLen; i++) {
        if ((i * iTime) + (numRows - 1) < iSLen) {
            psRes[iSResNum++] = s[(i * iTime) + (numRows - 1)];
        }
    }
    psRes[iSResNum] = '\0';

    return psRes;
}

int main() {
    char s[] = "PAYPALISHIRING";
    int iNumRow = 4;
    char *psRes = NULL;

    psRes = convert(s, iNumRow);
    printf("%s\n", psRes);
}