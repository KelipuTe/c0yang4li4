#include <stdio.h>
#include <stdlib.h>
#include <time.h>

extern void shuChuXuLie(int *, int );

/**
 * 插入排序
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
    // 认为第一个元素有序，排序从第二个元素开始
    for (int i = 1; i < daiPaiXuLen; i++)
    {
        int j = i;
        // 待排序元素
        int tNum = daiPaiXuArr[j];
        while (j > 0 && tNum < daiPaiXuArr[j - 1])
        {
            // 如果比前面小，就往前移动，直到移动到第一位
            daiPaiXuArr[j] = daiPaiXuArr[j - 1];
            j--;
        }
        // 插入有序序列
        daiPaiXuArr[j] = tNum;
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