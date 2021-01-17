#include <stdio.h>
#include <stdlib.h>
#include <time.h>

extern void shuChuXuLie(int *, int);

/**
 * 冒泡排序
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

    // 记录最后一个被交换的元素的位置
    int lastExchangeIndex = daiPaiXuLen - 1;
    for (int i = 0; i < daiPaiXuLen - 1; i++)
    {
        // 判断是否有元素交换
        int isSorted = 0;
        // 只需要比较到最后一个被交换的元素的位置
        int lastSortedIndex = lastExchangeIndex;
        for (int j = 0; j < lastSortedIndex; j++)
        {
            if (daiPaiXuArr[j] > daiPaiXuArr[j + 1])
            {
                int tNum = daiPaiXuArr[j];
                daiPaiXuArr[j] = daiPaiXuArr[j + 1];
                daiPaiXuArr[j + 1] = tNum;
                isSorted = 1;
                lastExchangeIndex = j;
            }
        }
        if (isSorted == 0)
        {
            // 如果一轮排序没有元素被交换，则序列已经有序
            break;
        }
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