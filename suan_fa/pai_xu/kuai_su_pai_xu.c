#include <stdio.h>
#include <stdlib.h>
#include <time.h>

extern void kuaiSuPaiXu(int *, int, int);
extern void shuChuXuLie(int *, int);

/**
 * 快速排序
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

    kuaiSuPaiXu(&daiPaiXuArr, 0, daiPaiXuLen - 1);

    printf("pai2xu4hou4:");
    shuChuXuLie(&daiPaiXuArr, daiPaiXuLen);

    return 0;
}

/**
 * 快速排序递归分组
 */
void kuaiSuPaiXu(int *daiPaiXuArr, int startIndex, int endIndex)
{
    if (startIndex >= endIndex)
    {
        return;
    }
    int i = startIndex;
    int j = endIndex;
    int tNum = 0;
    // 设定第一个元素作为基准元素
    int midNum = daiPaiXuArr[startIndex];
    // 这里两个循环会来回移动这个基准元素，最后基准元素会把序列分为，前半部分小于基准的，和后半部分大于基准的
    while (j > i)
    {
        // 从后往前找找一个比基准小的，和基准换位置
        if (daiPaiXuArr[j] < midNum)
        {
            tNum = daiPaiXuArr[i];
            daiPaiXuArr[i] = daiPaiXuArr[j];
            daiPaiXuArr[j] = tNum;
            for (i = i + 1; i < j; i++)
            {
                // 再从前往后找，找一个比基准大的，和基准换位置
                if (daiPaiXuArr[i] > midNum)
                {
                    tNum = daiPaiXuArr[j];
                    daiPaiXuArr[j] = daiPaiXuArr[i];
                    daiPaiXuArr[i] = tNum;
                    break;
                }
            }
        }
        j--;
    }
    // 上面的循环i最后会停在基准的坐标上，分别递归处理前半部分和后半部分，
    kuaiSuPaiXu(daiPaiXuArr, startIndex, i);
    kuaiSuPaiXu(daiPaiXuArr, i + 1, endIndex);
}

void shuChuXuLie(int *daiPaiXuArr, int daiPaiXuLen)
{
    for (int i = 0; i < daiPaiXuLen; i++)
    {
        printf("%d,", daiPaiXuArr[i]);
    }
    printf("\n");
}