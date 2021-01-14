#include <stdio.h>
#include <stdlib.h>
#include <time.h>

extern void shuChuXuLie(int *daiPaiXuArr, int daiPaiXuLen);

/**
 * 希尔排序
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
    // 按一定的跨度分组
    int range = (int)(daiPaiXuLen / 2);
    while (range > 0)
    {
        // 组内进行插入排序
        for (int i = range; i < daiPaiXuLen; i++)
        {
            int tNum = daiPaiXuArr[i];
            int j = i - range;
            while (j >= 0 && daiPaiXuArr[j] > tNum)
            {
                daiPaiXuArr[j + range] = daiPaiXuArr[j];
                j -= range;
            }
            daiPaiXuArr[j + range] = tNum;
        }
        // 重新设置一个更小的跨度
        range = (int)(range / 2);
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