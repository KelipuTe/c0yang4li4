#include <stdio.h>

/*#####leetcode70-爬楼梯#####*/

int climbStairs(int n) {
    if (n <= 1) {
        return 1;
    } else if (n == 2) {
        return 2;
    } else {
        int i = 2, j = 1, k = 0, m = 3;
        while (m <= n) {
            k = j;
            j = i;
            i = j + k;
            // printf("n=%d;%d\n", m, i);
            m++;
        }
        return i;
    }
}

int main() {
    int iNum = 5;
    int iRes = 0;

    iRes = climbStairs(iNum);
    printf("%d", iRes);
}