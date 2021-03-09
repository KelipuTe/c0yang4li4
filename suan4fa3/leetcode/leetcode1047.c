#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *removeDuplicates(char *S) {
    int iSLen = strlen(S);
    char *psRes = malloc(sizeof(char) * (iSLen + 1));
    memset(psRes, 0, sizeof(char) * (iSLen + 1));
    int iSResNum = 0;

    if (iSLen <= 0) {
        free(psRes);

        return "";
    }

    psRes[0] = S[0];
    for (int i = 1; i < iSLen; i++) {
        if (iSResNum < 0 || psRes[iSResNum] != S[i]) {
            iSResNum++;
            psRes[iSResNum] = S[i];
        } else {
            iSResNum--;
        }
    }
    psRes[iSResNum + 1] = '\0';

    return psRes;
}

int main() {
    char s[] = "abbaca";
    int *psRes = NULL;

    psRes = removeDuplicates(s);
    printf("%s\n", psRes);
}