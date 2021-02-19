#include <stdio.h>
#include <string.h>

/*#####leetcode5-最长回文子串#####*/

char *longestPalindrome(char *s)
{
    int iStrLen = 0, iIndexZuo = 0, iIndexYou = 0;

    iStrLen = strlen(s);
    if (iStrLen <= 1)
    {
        return s;
    }
    for (int i = 0; i < iStrLen; i++)
    {
        int iZuo = i - 1, iYou = i + 1;
        // 首先判断中间是不是有连续的相同的字符
        while (iZuo >= 0 && *(s + iZuo) == *(s + i))
        {
            iZuo--;
        }
        while (iYou < iStrLen && *(s + iYou) == *(s + i))
        {
            iYou++;
        }
        if (iZuo < 0 || iYou >= iStrLen)
        {
            // 连续的字符直接到边界了
            iZuo++;
            iYou--;
            // 比较以前找到的和这次找到的回文子串的长度
            if ((iYou - iZuo) >= 0 && (iYou - iZuo) > (iIndexYou - iIndexZuo))
            {
                iIndexZuo = iZuo;
                iIndexYou = iYou;
            }
        }
        else
        {
            // 判断连续字符加上外侧字符是不是回文字符串
            while (iZuo >= 0 && iYou < iStrLen && *(s + iZuo) == *(s + iYou))
            {
                iZuo--;
                iYou++;
            }
            iZuo++;
            iYou--;
            if ((iYou - iZuo) >= 0 && (iYou - iZuo) > (iIndexYou - iIndexZuo))
            {
                iIndexZuo = iZuo;
                iIndexYou = iYou;
            }
        }
    }
    // 这里如果新建参数，会碰到参数作用域的问题，所以直接改原来的字符串
    *(s + iIndexYou + 1) = '\0';

    return s + iIndexZuo;
}

int main()
{
    char sStr[] = "babad";
    char *psRes = NULL;

    psRes = longestPalindrome(sStr);
    printf("hui2wen2zi3chuan4:%s\n", psRes);
}