#include <stdio.h>
#include <stdlib.h>
#include <time.h>

extern void shuChuXuLie(int *daiPaiXuArr, int daiPaiXuLen);

/**
 * 选择排序
 */
int main()
{
    int daiPaiXuArr[10];
    int daiPaiXuLen = 10;
    srand(time(NULL));
    for (int i = 0; i < daiPaiXuLen; i++)
    {
        daiPaiXuArr[i] = (rand() % 99) + 1;
    }
    printf("pai2xu4qian2:");
    shuChuXuLie(&daiPaiXuArr, daiPaiXuLen);
    for (int i = 0; i < daiPaiXuLen; i++)
    {
        // 第n次循环找到第n小的那个元素
        int minIndex = i;
        for (int j = i; j < daiPaiXuLen; j++)
        {
            if (daiPaiXuArr[j] < daiPaiXuArr[minIndex])
            {
                minIndex = j;
            }
        }
        // 把第n小的值和序列第n个位置的元素交换
        int tNum = daiPaiXuArr[i];
        daiPaiXuArr[i] = daiPaiXuArr[minIndex];
        daiPaiXuArr[minIndex] = tNum;
    }
    printf("pai2xu4hou4:");
    shuChuXuLie(&daiPaiXuArr, daiPaiXuLen);
    return 0;
}

void shuChuXuLie(int *daiPaiXuArr, int daiPaiXuLen)
{
    for (int i = 0; i < daiPaiXuLen; i++)
    {
        printf("%d,", daiPaiXuArr[i]);
    }
    printf("\n");
}