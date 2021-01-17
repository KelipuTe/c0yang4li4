#include <stdio.h>
#include <stdlib.h>
#include <time.h>

extern void guiBinPaiXu(int *, int, int);
extern void heBinXuLie(int *, int, int, int);
extern void shuChuXuLie(int *, int);

/**
 * 归并排序
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

    guiBinPaiXu(&daiPaiXuArr, 0, daiPaiXuLen - 1);

    printf("pai2xu4hou4:");
    shuChuXuLie(&daiPaiXuArr, daiPaiXuLen);

    return 0;
}

/**
 * 归并排序递归分组
 */
void guiBinPaiXu(int *daiPaiXuArr, int startIndex, int endIndex)
{
    int midIndex = 0;
    if (startIndex < endIndex)
    {
        midIndex = (int)((startIndex + endIndex) / 2);
        guiBinPaiXu(daiPaiXuArr, startIndex, midIndex);
        guiBinPaiXu(daiPaiXuArr, midIndex + 1, endIndex);
        heBinXuLie(daiPaiXuArr, startIndex, midIndex, endIndex);
    }
}

/**
 * 归并排序合并序列
 */
void heBinXuLie(int *daiPaiXuArr, int startIndex, int midIndex, int endIndex)
{
    int i = startIndex;
    int j = midIndex + 1;
    int k = startIndex;
    // 使用一个临时数组保存本次归并的结果
    int tPaiXuArr[10];
    while (i < midIndex + 1 && j < endIndex + 1)
    {
        // 当两个序列都没有到头，需要比较哪个序列的第一个元素更小
        if (daiPaiXuArr[i] >= daiPaiXuArr[j])
        {
            tPaiXuArr[k++] = daiPaiXuArr[j++];
        }
        else
        {
            tPaiXuArr[k++] = daiPaiXuArr[i++];
        }
    }
    while (i < midIndex + 1)
    {
        // 当前面的序列已经到头，直接把后面序列的元素依次赋值
        tPaiXuArr[k++] = daiPaiXuArr[i++];
    }
    while (j < endIndex + 1)
    {
        // 当后面的序列已经到头，直接把前面序列的元素依次赋值
        tPaiXuArr[k++] = daiPaiXuArr[j++];
    }
    for (i = startIndex; i < endIndex + 1; i++)
    {
        // 把排序好的序列替换到原序列的位置
        daiPaiXuArr[i] = tPaiXuArr[i];
    }
}

void shuChuXuLie(int *daiPaiXuArr, int daiPaiXuLen)
{
    for (int i = 0; i < daiPaiXuLen; i++)
    {
        printf("%d,", daiPaiXuArr[i]);
    }
    printf("\n");
}