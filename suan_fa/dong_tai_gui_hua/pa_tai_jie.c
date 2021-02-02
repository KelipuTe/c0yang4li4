#include <stdio.h>
#include <windows.h>

/*#####动态规划：爬台阶问题#####*/

/*
 * 一个人爬楼梯，每次只能爬1个台阶或2个台阶。
 * 假设有n个台阶，那么这个人有多少种不同的爬楼梯方法？
 */

// 暴力递归
extern long long baoLiDiGui(int);
// 动态规划
extern long long dongTaiGuiHua(int);

int main()
{
    int iSteps = 50;
    DWORD tStart1, tStop1, tStart2, tStop2;

    tStart1 = GetTickCount();
    printf("bao4li4di4gui1:%lld\n", baoLiDiGui(iSteps));
    tStop1 = GetTickCount();
    printf("hao4shi2:%dms\n", tStop1 - tStart1);

    tStart2 = GetTickCount();
    printf("dong4tai4gui1hua4:%lld\n", dongTaiGuiHua(iSteps));
    tStop2 = GetTickCount();
    printf("hao4shi2:%dms\n", tStop2 - tStart2);

    return 0;
}

long long baoLiDiGui(int iSteps)
{
    if (iSteps == 0)
    {
        return 0;
    }
    else if (iSteps == 1)
    {
        return 1;
    }
    else if (iSteps == 2)
    {
        return 2;
    }
    else
    {
        return baoLiDiGui(iSteps - 1) + baoLiDiGui(iSteps - 2);
    }
}

long long dongTaiGuiHua(int iSteps)
{
    long long l0, l1, l2;

    if (iSteps == 0)
    {
        return 0;
    }
    else if (iSteps == 1)
    {
        return 1;
    }
    else if (iSteps == 2)
    {
        return 2;
    }
    else
    {
        l0 = 0;
        l1 = 1;
        l2 = 2;
        for (int i = 3; i < iSteps + 1; i++)
        {
            l0 = l1;
            l1 = l2;
            l2 = l0 + l1;
        }
    }
    return l2;
}