#include <stdio.h>

/*#####leetcode69-x的平方根#####*/

int mySqrt(int x) {
    long long iLeft = 0, iRight = 0, iMiddle = 0;

    iRight = (long long)(x / 2) + 1;
    while (iLeft <= iRight) {
        iMiddle = (long long)((iLeft + iRight) / 2);
        if (iMiddle * iMiddle < x) {
            if ((iMiddle + 1) * (iMiddle + 1) > x) {
                return iMiddle;
            }
            iLeft = iMiddle + 1;
        } else if (iMiddle * iMiddle > x) {
            if ((iMiddle - 1) * (iMiddle - 1) < x) {
                return iMiddle - 1;
            }
            iRight = iMiddle - 1;
        } else {
            return iMiddle;
        }
    }
    return iMiddle;
}

int main() {
    int iNum = 2147395599;
    // int iNum = 35;
    // int iNum = 4;
    // int iNum = 0;
    int iRes = 0;

    iRes = mySqrt(iNum);
    printf("%d", iRes);
}