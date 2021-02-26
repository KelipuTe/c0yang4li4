#include <stdio.h>

/*#####leetcode121-买卖股票的最佳时机#####*/

int maxProfit(int *prices, int pricesSize) {
    int iLiRunMax = 0, iJiaGeMin = prices[0], tiLiRun = 0;

    for (int i = 1; i < pricesSize; i++) {
        tiLiRun = prices[i] - iJiaGeMin;
        if (tiLiRun > iLiRunMax) {
            iLiRunMax = tiLiRun;
        }
        if (prices[i] < iJiaGeMin) {
            iJiaGeMin = prices[i];
        }
    }

    return iLiRunMax;
}

int main() {
    int iarrPrice[] = {7, 1, 5, 3, 6, 4};
    int iPriceLen = 6;
    // int iarrPrice[] = {7, 6, 4, 3, 1};
    // int iPriceLen = 5;
    int iLiRunMax = 0;

    iLiRunMax = maxProfit(iarrPrice, iPriceLen);
    printf("%d\n", iLiRunMax);
}