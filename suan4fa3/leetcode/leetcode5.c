#include <stdio.h>
#include <string.h>

/*#####leetcode5-最长回文子串#####*/

char *longestPalindrome(char *s) {
    int iStrLen = 0, iIndexZuo = 0, iIndexYou = 0, tiZuo = 0, tiYou = 0;

    iStrLen = strlen(s);
    if (iStrLen <= 1) {
        return s;
    }
    for (int i = 0; i < iStrLen; i++) {
        tiZuo = i - 1;
        tiYou = i + 1;
        // 首先判断中间是不是有连续的相同的字符
        while (tiZuo >= 0 && *(s + tiZuo) == *(s + i)) {
            tiZuo--;
        }
        while (tiYou < iStrLen && *(s + tiYou) == *(s + i)) {
            tiYou++;
        }
        if (tiZuo < 0 || tiYou >= iStrLen) {
            // 连续的字符直接到边界了
            tiZuo++;
            tiYou--;
            // 比较以前找到的和这次找到的回文子串的长度
            if ((tiYou - tiZuo) >= 0 && (tiYou - tiZuo) > (iIndexYou - iIndexZuo)) {
                iIndexZuo = tiZuo;
                iIndexYou = tiYou;
            }
        } else {
            // 判断连续字符加上外侧字符是不是回文字符串
            while (tiZuo >= 0 && tiYou < iStrLen && *(s + tiZuo) == *(s + tiYou)) {
                tiZuo--;
                tiYou++;
            }
            tiZuo++;
            tiYou--;
            if ((tiYou - tiZuo) >= 0 && (tiYou - tiZuo) > (iIndexYou - iIndexZuo)) {
                iIndexZuo = tiZuo;
                iIndexYou = tiYou;
            }
        }
    }
    // 这里如果新建参数，会碰到参数作用域的问题，所以直接改原来的字符串
    s[iIndexYou + 1] = '\0';

    return s + iIndexZuo;
}

int main() {
    char sStr[] = "babad";
    // char sStr[] = "cbbd";
    // char sStr[] = "a";
    // char sStr[] = "ac";
    char *psRes = NULL;

    psRes = longestPalindrome(sStr);
    printf("%s\n", psRes);
}