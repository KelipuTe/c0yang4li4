#include <math.h>
#include <stdio.h>

/*#####leetcode11-盛最多水的容器#####*/

int maxArea(int *height, int heightSize) {
    int iZuo = 0, iYou = heightSize - 1, iMaxArea = 0;
    iMaxArea = (int)fmin(height[iZuo], height[iYou]) * (iYou - iZuo);
    while (iZuo < iYou) {
        if (height[iZuo] < height[iYou]) {
            iZuo++;
        } else {
            iYou--;
        }
        if ((int)fmin(height[iZuo], height[iYou]) * (iYou - iZuo) > iMaxArea) {
            iMaxArea = (int)fmin(height[iZuo], height[iYou]) * (iYou - iZuo);
        }
    }

    return iMaxArea;
}

int main() {
    int iarr[] = {1, 8, 6, 2, 5, 4, 8, 3, 7};
    // int iarr[] = {1, 1};
    int iArrLen = sizeof(iarr) / sizeof(int);
    int iMaxArea = 0;

    iMaxArea = maxArea(iarr, iArrLen);
    printf("%d\n", iMaxArea);
}