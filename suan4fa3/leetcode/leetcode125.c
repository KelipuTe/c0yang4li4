#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*#####leetcode125-验证回文串#####*/

int isPalindrome(char *s) {
    int iSLen = strlen(s), iTsLen = 0;
    char *ts = (char *)malloc(sizeof(char) * (iSLen + 1));
    memset(ts, 0, sizeof(char) * (iSLen + 1));

    // 筛出数字和大小写字母
    int j = 0;
    while (j < iSLen) {
        if (isdigit(s[j])) {
            ts[iTsLen++] = s[j];
        } else if (isalpha(s[j])) {
            if (isupper(s[j])) {
                ts[iTsLen++] = tolower(s[j]);
            } else {
                ts[iTsLen++] = s[j];
            }
        }
        j++;
    }
    ts[iTsLen] = '\0';

    // 首尾比对
    j = 0;
    while (j < (iTsLen / 2)) {
        if (ts[j] != ts[iTsLen - 1 - j]) {
            return 0;
        }
        j++;
    }

    return 1;
}

int main() {
    char ts[] = "A man, a plan, a canal: Panama";
    int ibRes = 0;

    ibRes = isPalindrome(ts);
    printf("%d\n", ibRes);
}