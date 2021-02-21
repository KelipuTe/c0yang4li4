#include <stdio.h>
#include <stdlib.h>

/*#####无向图-邻接表#####*/

// 无向图顶点数
#define DING_DIAN_SHU 8

// 邻接表结点
typedef struct LingJieBiaoJieDian
{
    // 顶点
    int iDingDian;
    // 下一个结点的指针
    struct LingJieBiaoJieDian *pNext;
} LJBJD;

// 无向图邻接表
LJBJD *pArrWuXiangTu[DING_DIAN_SHU] = {NULL};

// 添加邻接表结点
extern void tianJiaJieDian(int, int);
// 输出无向图
extern void shuChuWuXiangTu();
// 广度优先遍历
extern void guangDuYouXianBianLi(int[DING_DIAN_SHU]);
// 深度优先遍历
extern void shenDuYouXianBianLi(int, int[DING_DIAN_SHU]);

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
        // 无向图是对称的
        tianJiaJieDian(iArr2LuJing[i][0], iArr2LuJing[i][1]);
        tianJiaJieDian(iArr2LuJing[i][1], iArr2LuJing[i][0]);
    }

    printf("wu2xiang4tu2-lin2jie1biao3:\n");
    shuChuWuXiangTu();

    printf("guang3du4you1xian1bian4li4:");
    guangDuYouXianBianLi(iArrDingDianFangWen1);
    printf("\n");

    printf("shen1du4you1xian1bian4li4:");
    shenDuYouXianBianLi(0, iArrDingDianFangWen2);
    printf("\n");

    return 0;
}

void tianJiaJieDian(int iDingDian1, int iDingDian2)
{
    // 构造邻接表结点
    LJBJD *tpLJBJD = (LJBJD *)malloc(sizeof(LJBJD));
    tpLJBJD->iDingDian = iDingDian2;
    tpLJBJD->pNext = NULL;

    // 插入节点到顶点邻接表的末尾
    if (pArrWuXiangTu[iDingDian1] == NULL)
    {
        pArrWuXiangTu[iDingDian1] = tpLJBJD;
    }
    else
    {
        LJBJD *tpNow = pArrWuXiangTu[iDingDian1];
        while (tpNow->pNext != NULL)
        {
            tpNow = tpNow->pNext;
        }
        tpNow->pNext = tpLJBJD;
    }
}

void shuChuWuXiangTu()
{
    LJBJD *tpNow = NULL;

    for (int i; i < DING_DIAN_SHU; i++)
    {
        tpNow = pArrWuXiangTu[i];
        printf("%d:", i);
        while (tpNow != NULL)
        {
            printf("%d,", tpNow->iDingDian);
            tpNow = tpNow->pNext;
        }
        printf("\n");
    }
}

void guangDuYouXianBianLi(int iArrDingDianFangWen[DING_DIAN_SHU])
{
    int tiDingDian = -1;
    LJBJD *tpNow = NULL;

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
            // 拿到这个顶点的领接表数据
            tpNow = pArrWuXiangTu[tiDingDian];
            while (tpNow != NULL)
            {
                // 优先遍历一行，把遇到的顶点都入队
                tiDingDian = tpNow->iDingDian;
                if (iArrDingDianFangWen[tiDingDian] == 0)
                {
                    printf("%d,", tiDingDian);
                    iArrDingDianFangWen[tiDingDian] = 1;
                    ruDui(tiDingDian);
                }
                tpNow = tpNow->pNext;
            }
            tiDingDian = chuDui();
        }
    }
}

void shenDuYouXianBianLi(int i, int iArrDingDianFangWen[DING_DIAN_SHU])
{
    LJBJD *tpNow = NULL;

    printf("%d,", i);
    iArrDingDianFangWen[i] = 1;
    // 拿到这个顶点的领接表数据
    tpNow = pArrWuXiangTu[i];
    while (tpNow != NULL)
    {
        if (iArrDingDianFangWen[tpNow->iDingDian] != 1)
        {
            // 如果发现没访问过的结点就向下递归
            shenDuYouXianBianLi(tpNow->iDingDian, iArrDingDianFangWen);
        }
        // 这里无论有没有发现没访问过的结点都要把指针后移
        tpNow = tpNow->pNext;
    }
}

/*#####队列#####*/

void ruDui(int iDingDian)
{
    DLJD *tpDLJD = (DLJD *)malloc(sizeof(DLJD));

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