#include <stdio.h>
#include <math.h>

/*#####leetcode9-回文数#####*/

int isPalindrome(int x)
{
    int iArrNum[12] = {0};
    int iNumLen = 1;

    if (x < 0)
    {
        return 0;
    }
    else if (x == 0)
    {
        return 1;
    }
    int i = 0;
    while (x > 0)
    {
        iArrNum[i] = x % 10;
        x = (int)(x / 10);
        i++;
    }
    // 这里长度不需要额外+1
    iNumLen = i;
    for (int i = 0; i < (int)(iNumLen / 2); i++)
    {
        if (iArrNum[i] != iArrNum[iNumLen - 1 - i])
        {
            return 0;
        }
    }
    return 1;
}

// 不用数组或者字符串
int isPalindrome2(int x)
{
    int iNumLen = 1, iZuo = 0, iYou = 0;

    if (x < 0)
    {
        return 0;
    }
    else if (x == 0)
    {
        return 1;
    }

    // 计算数字长度
    while (x >= pow(10, iNumLen))
    {
        iNumLen++;
    }
    // 依次比较对应位置
    for (int i = 0; i < (int)(iNumLen / 2); i++)
    {
        iZuo = (int)(x / pow(10, iNumLen - 1 - i)) % (int)pow(10, 1 + i);
        iZuo %= 10;
        iYou = (int)(x % (int)pow(10, 1 + i) / pow(10, i));
        if (iZuo != iYou)
        {
            return 0;
        }
    }
    return 1;
}

int main()
{
    int iNum = 12321, iResNum = 0;
    iResNum = isPalindrome2(iNum);
    printf("%d,%d\n", iNum, iResNum);
}