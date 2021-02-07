#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*#####二叉树#####*/

// 二叉树结点
typedef struct ErChaShuJieDian
{
    // 结点值，约定结点值都大于0
    int iShuZhi;
    // 左结点
    struct ErChaShuJieDian *pZuo;
    // 右结点
    struct ErChaShuJieDian *pYou;
    // 结点层数
    int iJieDianCengShu;
} ECSJD;

// 头指针
ECSJD *pErChaShuHead = NULL;

// 从数组构造二叉树，注意参数pNow是二级指针
extern void gouZaoErChaShu(ECSJD **, int *, int, int);
// 前序遍历，根左右
extern void qianXuBianLi(ECSJD *);
// 中序遍历，左根右
extern void zhongXuBianLi(ECSJD *);
// 后序遍历，左右根
extern void houXuBianLi(ECSJD *);
// 计算二叉树深度
extern int jiSuanErChaShuShenDu(ECSJD *);
// 广度优先遍历
extern void guangDuYouXianBianLi();
// 深度优先遍历
extern void shenDuYouXianBianLi();

/*#####队列#####*/

typedef struct DuiLieJieDian
{
    ECSJD *pErChaShu;
    struct DuiLieJieDian *pNext;
} DLJD;

DLJD *pDuiLieHead = NULL;
DLJD *pDuiLieTail = NULL;

extern void ruDui(ECSJD *, int);
extern ECSJD *chuDui();

/*#####栈#####*/

typedef struct ZhanJieDian
{
    ECSJD *pErChaShu;
    struct ZhanJieDian *pNext;
} ZJD;

ZJD *pZhanDing = NULL;

extern void ruZhan(ECSJD *);
extern ECSJD *chuZhan();

/*#####实现代码#####*/

int main()
{
    int iArrYuanSuBiao[] = {1, 2, 3, 4, 5, 6, 7, 0, 0, 10, 11};
    int iYuanSuBiaoLen = sizeof(iArrYuanSuBiao) / sizeof(int);
    gouZaoErChaShu(&pErChaShuHead, &iArrYuanSuBiao, iYuanSuBiaoLen, 1);

    printf("qian2xu4bian4li4:");
    qianXuBianLi(pErChaShuHead);
    printf("\n");

    printf("zhong1xu4bian4li4:");
    zhongXuBianLi(pErChaShuHead);
    printf("\n");

    printf("hou4xu4bian4li4:");
    houXuBianLi(pErChaShuHead);
    printf("\n");

    ("er4cha1shu4shen1du4:%d\n", jiSuanErChaShuShenDu(pErChaShuHead));

    printf("guang3du4you1xian1bian4li4:");
    guangDuYouXianBianLi();
    printf("\n");

    printf("shen1du4you1xian1bian4li4:");
    shenDuYouXianBianLi();
    printf("\n");
}

/*#####二叉树#####*/

void gouZaoErChaShu(ECSJD **ppNow, int *pYuanSuBiao, int iYuanSuBiaoLen, int index)
{
    if (index <= iYuanSuBiaoLen)
    {
        if (pYuanSuBiao[index - 1] == 0)
        {
            // 识别无效值
            *ppNow = NULL;

            return;
        }
        else
        {
            *ppNow = (ECSJD *)malloc(sizeof(ECSJD));
            if (*ppNow == NULL)
            {
                printf("nei4cun2fen1pei4shi1bai4!\n");
                exit(0);
            }
            (*ppNow)->iShuZhi = pYuanSuBiao[index - 1];
            (*ppNow)->pZuo = NULL;
            (*ppNow)->pYou = NULL;
            (*ppNow)->iJieDianCengShu = 0;
            // 这里把这次构造的结点的左右结点传递下去，传递的参数其实是指向左右结点的指针
            // 但是不能简单地传递指针，直接把指针传下去就变形参了，所以传递一个二级指针
            gouZaoErChaShu(&((*ppNow)->pZuo), pYuanSuBiao, iYuanSuBiaoLen, index * 2);
            gouZaoErChaShu(&((*ppNow)->pYou), pYuanSuBiao, iYuanSuBiaoLen, index * 2 + 1);
        }
    }
}

void qianXuBianLi(ECSJD *pNow)
{
    if (pNow == NULL)
    {
        return;
    }
    printf("%d,", pNow->iShuZhi);
    qianXuBianLi(pNow->pZuo);
    qianXuBianLi(pNow->pYou);
}

void zhongXuBianLi(ECSJD *pNow)
{
    if (pNow == NULL)
    {
        return;
    }
    zhongXuBianLi(pNow->pZuo);
    printf("%d,", pNow->iShuZhi);
    zhongXuBianLi(pNow->pYou);
}

void houXuBianLi(ECSJD *pNow)
{
    if (pNow == NULL)
    {
        return;
    }
    houXuBianLi(pNow->pZuo);
    houXuBianLi(pNow->pYou);
    printf("%d,", pNow->iShuZhi);
}

int jiSuanErChaShuShenDu(ECSJD *pNow)
{
    int iZuoShenDu = 0;
    int iYouShenDu = 0;
    if (pNow == NULL)
    {
        return 0;
    }
    iZuoShenDu = jiSuanErChaShuShenDu(pNow->pZuo);
    iYouShenDu = jiSuanErChaShuShenDu(pNow->pYou);

    return (int)fmax(iZuoShenDu, iYouShenDu) + 1;
}

void guangDuYouXianBianLi()
{
    int iJieDianCengShu = 1;
    ECSJD *pErChaShu = NULL;

    ruDui(pErChaShuHead, iJieDianCengShu);
    pErChaShu = chuDui();
    while (pErChaShu != NULL)
    {
        // 持续遍历，直到队列为空
        printf("%d-%d,", pErChaShu->iJieDianCengShu, pErChaShu->iShuZhi);
        if (pErChaShu->pZuo != NULL)
        {
            // 左结点先入队，先遍历
            ruDui(pErChaShu->pZuo, pErChaShu->iJieDianCengShu + 1);
        }
        if (pErChaShu->pYou != NULL)
        {
            // 右结点后入队，后遍历
            ruDui(pErChaShu->pYou, pErChaShu->iJieDianCengShu + 1);
        }
        pErChaShu = chuDui();
    }
}

void shenDuYouXianBianLi()
{
    ECSJD *pErChaShu = NULL;

    ruZhan(pErChaShuHead);
    pErChaShu = chuZhan();
    while (pErChaShu != NULL)
    {
        // 持续遍历，直到栈为空
        printf("%d,", pErChaShu->iShuZhi);
        if (pErChaShu->pYou != NULL)
        {
            // 右结点先入栈，后遍历
            ruZhan(pErChaShu->pYou);
        }
        if (pErChaShu->pZuo != NULL)
        {
            // 左结点后入栈，先遍历
            ruZhan(pErChaShu->pZuo);
        }
        pErChaShu = chuZhan();
    }
}

/*#####队列#####*/

void ruDui(ECSJD *pErChaShu, int iJieDianCengShu)
{
    DLJD *pTemp = (DLJD *)malloc(sizeof(DLJD));
    // 入队时记录层数
    pErChaShu->iJieDianCengShu = iJieDianCengShu;
    pTemp->pErChaShu = pErChaShu;
    pTemp->pNext = NULL;
    if (pDuiLieHead == NULL)
    {
        pDuiLieHead = pDuiLieTail = pTemp;
    }
    else
    {
        pDuiLieTail->pNext = pTemp;
        pDuiLieTail = pDuiLieTail->pNext;
    }
}

ECSJD *chuDui()
{
    ECSJD *pErChaShu = NULL;
    DLJD *pNow = NULL;

    if (pDuiLieHead == NULL)
    {
        return pErChaShu;
    }
    pNow = pDuiLieHead;
    pErChaShu = pDuiLieHead->pErChaShu;
    pDuiLieHead = pDuiLieHead->pNext;
    free(pNow);

    return pErChaShu;
}

/*#####栈#####*/

void ruZhan(ECSJD *pErChaShu)
{
    ZJD *pTemp = (ZJD *)malloc(sizeof(ZJD));

    pTemp->pErChaShu = pErChaShu;
    if (pZhanDing == NULL)
    {
        pTemp->pNext = NULL;
        pZhanDing = pTemp;
    }
    else
    {
        pTemp->pNext = pZhanDing;
        pZhanDing = pTemp;
    }
}

ECSJD *chuZhan()
{
    ECSJD *pErChaShu = NULL;
    ZJD *pNow = NULL;

    if (pZhanDing == NULL)
    {
        return pErChaShu;
    }
    pNow = pZhanDing;
    pErChaShu = pZhanDing->pErChaShu;
    pZhanDing = pZhanDing->pNext;
    free(pNow);

    return pErChaShu;
}