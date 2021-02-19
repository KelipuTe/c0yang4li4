#include <stdio.h>
#include <string.h>

/*#####leetcode3-无重复字符的最长子串#####*/

int lengthOfLongestSubstring(char *s)
{
    int iStrLen = 0, iIndexZuo = 0, iIndexYou = 0, iCharVal = -1, iLen = 0, iLenMax = 0;
    int iArrHash[128] = {0};

    iStrLen = strlen(s);
    if (iStrLen <= 1)
    {
        return 0;
    }
    while (iIndexYou < iStrLen)
    {
        // 将字符转换成数值
        printf("%c\n", *(s + iIndexYou));
        iCharVal = (int)*(s + iIndexYou);
        // 判断该字符是否出现过
        if (iArrHash[iCharVal] == 0)
        {
            // 没出现过，标记字符并增加子串长度
            iArrHash[iCharVal] = 1;
            iLen++;
            if (iLen > iLenMax)
            {
                iLenMax = iLen;
            }
        }
        else
        {
            // 出现过，移动左边的指针，直到碰到前一样的字符
            while (*(s + iIndexZuo) != *(s + iIndexYou))
            {
                // 中间出现的字符全部需要重置
                iCharVal = (int)*(s + iIndexZuo);
                iArrHash[iCharVal] = 0;
                iLen--;
                iIndexZuo++;
            }
            // 最后这里还需要移动一下左边的指针把前一次出现的一样的字符跳过去
            iIndexZuo++;
        }
        // 右边的指针移向后一个字符
        iIndexYou++;
    }

    return iLenMax;
}

int main()
{
    char sStr[] = "pwwkew";
    int iLenMax = 0;

    iLenMax = lengthOfLongestSubstring(sStr);
    printf("zi3chuan4chang2du2:%d\n", iLenMax);
}
