#include <stdio.h>
#include <string.h>

/*#####leetcode13-罗马数字转整数#####*/

int romanToInt(char *s) {
    int iStrLen = 0, iRoman = 0;

    iStrLen = strlen(s);
    // 最后一个字符单独处理
    for (int i = 0; i < iStrLen - 1; i++) {
        switch (s[i]) {
            case 'I':
                if (s[i + 1] == 'V' || s[i + 1] == 'X') {
                    iRoman -= 1;
                } else {
                    iRoman += 1;
                }
                break;
            case 'V':
                iRoman += 5;
                break;
            case 'X':
                if (s[i + 1] == 'L' || s[i + 1] == 'C') {
                    iRoman -= 10;
                } else {
                    iRoman += 10;
                }
                break;
            case 'L':
                iRoman += 50;
                break;
            case 'C':
                if (s[i + 1] == 'D' || s[i + 1] == 'M') {
                    iRoman -= 100;
                } else {
                    iRoman += 100;
                }
                break;
            case 'D':
                iRoman += 500;
                break;
            case 'M':
                iRoman += 1000;
                break;
        }
    }
    // 处理最后一个字符
    switch (s[iStrLen - 1]) {
        case 'I':
            iRoman += 1;
            break;
        case 'V':
            iRoman += 5;
            break;
        case 'X':
            iRoman += 10;
            break;
        case 'L':
            iRoman += 50;
            break;
        case 'C':
            iRoman += 100;
            break;
        case 'D':
            iRoman += 500;
            break;
        case 'M':
            iRoman += 1000;
            break;
    }

    return iRoman;
}

int main() {
    // char sRoman[] = "III";
    // char sRoman[] = "IV";
    // char sRoman[] = "IX";
    // char sRoman[] = "LVIII";
    char sRoman[] = "MCMXCIV";
    int iRoman = 0;

    iRoman = romanToInt(sRoman);
    printf("roman:%s,int:%d\n", sRoman, iRoman);
}