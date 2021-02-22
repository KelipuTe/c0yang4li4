#include <stdio.h>
#include <stdlib.h>

/*#####leetcode35-搜索插入位置#####*/

char *countAndSay(int n) {
    char *psStr, *psRes;
    int iCountIndex = 0, iNumIndex = 0;
    if (n == 1) {
        char *tp = "1";
        return tp;
    } else {
        psStr = (char *)malloc(sizeof(char) * 1024 * 8);
        psRes = countAndSay(n - 1);
        iCountIndex = 0;
        iNumIndex = 1;
        psStr[iCountIndex] = '1';
        psStr[iNumIndex] = psRes[0];
        for (int i = 1; psRes[i] != '\0'; i++) {
            if (psRes[i] == psStr[iNumIndex]) {
                psStr[iCountIndex]++;
            } else {
                iCountIndex += 2;
                iNumIndex += 2;
                psStr[iCountIndex] = '1';
                psStr[iNumIndex] = psRes[i];
            }
        }
        psStr[iNumIndex + 1] = '\0';
        // printf("%s\n", psStr);

        return psStr;
    }
}

int main() {
    countAndSay(30);
}
