#include <stdio.h>

/*#####leetcode7-整数反转#####*/

int reverse(int x)
{
    long iResNum = 0, iTimes = 1, iDiYiWei = 0;

    while (x != 0)
    {
        if (iDiYiWei == 0)
        {
            iDiYiWei = x % 10;
            if (iDiYiWei == 0)
            {
                // 原数字末尾是0的情况
                x = (int)(x / 10);
                continue;
            }
        }
        iResNum *= 10;
        if (iResNum != 0 && (iResNum / iTimes != iDiYiWei))
        {
            // 如果第一位的数字变了，那就是溢出了
            // 这里不太严谨，理论上需要校验上一次结果的所有数字在这一次结果的对应位置是否发生了变化
            return 0;
        }
        iResNum += x % 10;
        if (iResNum != 0 && (iResNum / iTimes != iDiYiWei))
        {
            return 0;
        }
        // 倍数这里利用了int可以保存1000000000
        iTimes *= 10;
        x = (int)(x / 10);
    }

    if ((int)iResNum != iResNum)
    {
        return 0;
    }
    return (int)iResNum;
}

int main()
{
    int iNum = 1534236464, iResNum = 0;
    iResNum = reverse(iNum);
    printf("%d,%d\n", iNum, iResNum);
}