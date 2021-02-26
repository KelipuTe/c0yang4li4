#include <stdio.h>

/*#####leetcode122-买卖股票的最佳时机#####*/

int maxProfit(int *prices, int pricesSize) {
    int iZongLiRun = 0, iJiaGeMin = prices[0], iJiaGeFront = prices[0], ibJiaGeZouShi = 0;

    for (int i = 1; i < pricesSize; i++) {
        if (ibJiaGeZouShi == 0 && iJiaGeFront < prices[i]) {
            ibJiaGeZouShi = 1;
        } else if (ibJiaGeZouShi == 1 && iJiaGeFront > prices[i]) {
            ibJiaGeZouShi = 0;
            iZongLiRun += (iJiaGeFront - iJiaGeMin);
            iJiaGeMin = prices[i];
        }
        if (prices[i] < iJiaGeMin) {
            iJiaGeMin = prices[i];
        }

        iJiaGeFront = prices[i];
    }
    if (ibJiaGeZouShi == 1) {
        iZongLiRun += (iJiaGeFront - iJiaGeMin);
    }

    return iZongLiRun;
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