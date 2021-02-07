#include <stdio.h>
#include <stdlib.h>

/*#####无向图-邻接矩阵#####*/

// 无向图顶点数
#define DING_DIAN_SHU 8

// 无向图邻接矩阵
int iArr2WuXiangTu[DING_DIAN_SHU][DING_DIAN_SHU] = {0};

// 输出无向图
extern void shuChuWuXiangTu();
// 深度优先遍历
extern void shenDuYouXianBianLi(int, int[DING_DIAN_SHU]);
// 广度优先遍历
extern void guangDuYouXianBianLi(int[DING_DIAN_SHU]);

/*#####队列#####*/

typedef struct DuiLieJieDian
{
    // 顶点
    int iDingDian;
    struct DuiLieJieDian *pNext;
} DLJD;

DLJD *pDuiLieHead = NULL;
DLJD *pDuiLieTail = NULL;

extern void ruDui(int);
extern int chuDui();

/*#####实现代码#####*/

int main()
{
    // 路径列表
    int iArr2LuJing[][2] = {
        {0, 1},
        {0, 5},
        {1, 2},
        {1, 6},
        {2, 3},
        {3, 6},
        {3, 7},
        {4, 5},
        {4, 7},
        {5, 1},
        {5, 6},
        {6, 7},
    };
    // 路径列表数量
    int iLuJingShu = 12;
    // 顶点访问情况：0=未访问；1=已访问；
    int iArrDingDianFangWen1[DING_DIAN_SHU] = {0};
    int iArrDingDianFangWen2[DING_DIAN_SHU] = {0};

    // 构造无向图邻接矩阵
    for (int i = 0; i < iLuJingShu; i++)
    {
        int iDingDian1 = iArr2LuJing[i][0];
        int iDingDian2 = iArr2LuJing[i][1];
        // 无向图是对称的
        iArr2WuXiangTu[iDingDian1][iDingDian2] = 1;
        iArr2WuXiangTu[iDingDian2][iDingDian1] = 1;
    }

    printf("wu2xiang4tu2-lin2jie1ju1zhen4:\n");
    shuChuWuXiangTu();
    printf("shen1du4you1xian1bian4li4:");
    shenDuYouXianBianLi(0, iArrDingDianFangWen1);
    printf("\n");
    printf("guang3du4you1xian1bian4li4:");
    guangDuYouXianBianLi(iArrDingDianFangWen2);
    printf("\n");

    return 0;
}

void shuChuWuXiangTu()
{
    for (int i = 0; i < DING_DIAN_SHU; i++)
    {
        for (int j = 0; j < DING_DIAN_SHU; j++)
        {
            printf("%d,", iArr2WuXiangTu[i][j]);
        }
        printf("\n");
    }
}

void shenDuYouXianBianLi(int i, int iArrDingDianFangWen[DING_DIAN_SHU])
{
    // 输出访问到的顶点
    printf("%d,", i);
    // 记录顶点访问情况
    iArrDingDianFangWen[i] = 1;
    // 遍历矩阵中对应顶点的行
    for (int j = 0; j < DING_DIAN_SHU; j++)
    {
        if (iArr2WuXiangTu[i][j] == 1 && iArrDingDianFangWen[j] == 0)
        {
            // 如果找到没有访问过的顶点，就访问该顶点
            shenDuYouXianBianLi(j, iArrDingDianFangWen);
        }
        // 这里是个递归，当里层顶点的行访问结束后，继续访问外层顶点的行
    }
}

void guangDuYouXianBianLi(int iArrDingDianFangWen[DING_DIAN_SHU])
{
    // 广度优先遍历需要用到队列，这里和二叉树的广度优先遍历有点类似
    int tiDingDian;

    for (int i = 0; i < DING_DIAN_SHU; i++)
    {
        if (iArrDingDianFangWen[i] == 1)
        {
            continue;
        }
        printf("%d,", i);
        iArrDingDianFangWen[i] = 1;
        ruDui(i);
        tiDingDian = chuDui();
        while (tiDingDian != -1)
        {
            // 持续遍历，直到队列为空
            for (int j = 0; j < DING_DIAN_SHU; j++)
            {
                // 优先遍历一行，把遇到的顶点都入队
                if (iArr2WuXiangTu[tiDingDian][j] == 1 && iArrDingDianFangWen[j] == 0)
                {
                    printf("%d,", j);
                    iArrDingDianFangWen[j] = 1;
                    ruDui(j);
                }
            }
            tiDingDian = chuDui();
        }
    }
}

/*#####队列#####*/

void ruDui(int iDingDian)
{
    DLJD *tpDLJD;

    tpDLJD = (DLJD *)malloc(sizeof(DLJD));
    tpDLJD->iDingDian = iDingDian;
    tpDLJD->pNext = NULL;
    if (pDuiLieHead == NULL)
    {
        pDuiLieHead = pDuiLieTail = tpDLJD;
    }
    else
    {
        pDuiLieTail->pNext = tpDLJD;
        pDuiLieTail = pDuiLieTail->pNext;
    }
}

int chuDui()
{
    DLJD *tpNow = NULL;
    int iDingDian = -1;

    if (pDuiLieHead == NULL)
    {
        return iDingDian;
    }
    tpNow = pDuiLieHead;
    iDingDian = pDuiLieHead->iDingDian;
    pDuiLieHead = pDuiLieHead->pNext;
    free(tpNow);

    return iDingDian;
}