#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*#####二叉树#####*/

/**
 * 二叉树结点
 */
struct ErChaShuJieDian
{
    // 结点值
    int num;
    // 左结点
    struct ErChaShuJieDian *pZuo;
    // 右结点
    struct ErChaShuJieDian *pYou;
    // 结点层数
    int jieDianCengShu;
};

// 头指针
struct ErChaShuJieDian *pErChaShuHead = NULL;

extern void chuShiHuaErChaShu();
extern void gouZaoErChaShu(int *, int, struct ErChaShuJieDian **, int);
extern void qianXuBianLi(struct ErChaShuJieDian *);
extern void zhongXuBianLi(struct ErChaShuJieDian *);
extern void houXuBianLi(struct ErChaShuJieDian *);
extern int jiSuanErChaShuShenDu(struct ErChaShuJieDian *);
extern void guangDuYouXianBianLi();
extern void shenDuYouXianBianLi();

/*#####队列#####*/

struct DuiLieJieDian
{
    struct ErChaShuJieDian *pErChaShu;
    struct DuiLieJieDian *pNext;
};

struct DuiLieJieDian *pDuiLieHead = NULL;
struct DuiLieJieDian *pDuiLieTail = NULL;

extern void ruDui(struct ErChaShuJieDian *, int);
extern struct ErChaShuJieDian *chuDui();

/*#####栈#####*/

struct ZhanJieDian
{
    struct ErChaShuJieDian *pErChaShu;
    struct ZhanJieDian *pNext;
};

struct ZhanJieDian *pZhanDing = NULL;

extern void ruZhan(struct ErChaShuJieDian *);
extern struct ErChaShuJieDian *chuZhan();

/**
 * 二叉树
 */
int main()
{
    int yuanSuBiao[] = {1, 2, 3, 4, 5, 6, 7, 0, 0, 10, 11};
    int yuanSuBiaoLen = sizeof(yuanSuBiao) / sizeof(int);
    gouZaoErChaShu(&yuanSuBiao, yuanSuBiaoLen, &pErChaShuHead, 1);

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

/**
 * 从数组构造二叉树
 * 注意参数pNow是二级指针
 */
void gouZaoErChaShu(int *yuanSuBiao, int yuanSuBiaoLen, struct ErChaShuJieDian **pNow, int index)
{
    if (index <= yuanSuBiaoLen)
    {
        if (yuanSuBiao[index - 1] == 0)
        {
            *pNow = NULL;

            return;
        }
        else
        {
            *pNow = (struct ErChaShuJieDian *)malloc(sizeof(struct ErChaShuJieDian));
            if (*pNow == NULL)
            {
                printf("nei4cun2fen1pei4shi1bai4!\n");
                exit(0);
            }
            (*pNow)->num = yuanSuBiao[index - 1];
            (*pNow)->pZuo = NULL;
            (*pNow)->pYou = NULL;
            (*pNow)->jieDianCengShu = 0;
            // 这里把这次构造的结点的左右结点传递下去，传递的参数其实是指向左右结点的指针
            // 但是不能简单地传递指针，直接把指针传下去就变形参了，所以传递一个二级指针
            gouZaoErChaShu(yuanSuBiao, yuanSuBiaoLen, &((*pNow)->pZuo), index * 2);
            gouZaoErChaShu(yuanSuBiao, yuanSuBiaoLen, &((*pNow)->pYou), index * 2 + 1);
        }
    }
}

/**
 * 前序遍历，根左右
 */
void qianXuBianLi(struct ErChaShuJieDian *pNow)
{
    if (pNow == NULL)
    {
        return;
    }
    printf("%d,", pNow->num);
    qianXuBianLi(pNow->pZuo);
    qianXuBianLi(pNow->pYou);
}

/**
 * 中序遍历，左根右
 */
void zhongXuBianLi(struct ErChaShuJieDian *pNow)
{
    if (pNow == NULL)
    {
        return;
    }
    zhongXuBianLi(pNow->pZuo);
    printf("%d,", pNow->num);
    zhongXuBianLi(pNow->pYou);
}

/**
 * 后序遍历，左右根
 */
void houXuBianLi(struct ErChaShuJieDian *pNow)
{
    if (pNow == NULL)
    {
        return;
    }
    houXuBianLi(pNow->pZuo);
    houXuBianLi(pNow->pYou);
    printf("%d,", pNow->num);
}

/**
 * 计算二叉树深度
 */
int jiSuanErChaShuShenDu(struct ErChaShuJieDian *pNow)
{
    int zuoShenDu = 0;
    int youShenDu = 0;
    if (pNow == NULL)
    {
        return 0;
    }
    zuoShenDu = jiSuanErChaShuShenDu(pNow->pZuo);
    youShenDu = jiSuanErChaShuShenDu(pNow->pYou);

    return (int)fmax(zuoShenDu, youShenDu) + 1;
}

/**
 * 广度优先遍历
 */
void guangDuYouXianBianLi()
{
    int jieDianCengShu = 1;
    struct ErChaShuJieDian *pErChaShu = NULL;

    ruDui(pErChaShuHead, jieDianCengShu);
    pErChaShu = chuDui();
    while (pErChaShu != NULL)
    {
        // 持续遍历，直到队列为空
        printf("%d-%d,", pErChaShu->jieDianCengShu, pErChaShu->num);
        if (pErChaShu->pZuo != NULL)
        {
            // 左结点先入队，先遍历
            ruDui(pErChaShu->pZuo, pErChaShu->jieDianCengShu + 1);
        }
        if (pErChaShu->pYou != NULL)
        {
            // 右结点后入队，后遍历
            ruDui(pErChaShu->pYou, pErChaShu->jieDianCengShu + 1);
        }
        pErChaShu = chuDui();
    }
}

/**
 * 深度优先遍历
 */
void shenDuYouXianBianLi()
{
    struct ErChaShuJieDian *pErChaShu = NULL;

    ruZhan(pErChaShuHead);
    pErChaShu = chuZhan();
    while (pErChaShu != NULL)
    {
        // 持续遍历，直到栈为空
        printf("%d,", pErChaShu->num);
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

void ruDui(struct ErChaShuJieDian *pErChaShu, int jieDianCengShu)
{
    struct DuiLieJieDian *pTemp = (struct DuiLieJieDian *)malloc(sizeof(struct DuiLieJieDian));
    // 入队时记录层数
    pErChaShu->jieDianCengShu = jieDianCengShu;
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

struct ErChaShuJieDian *chuDui()
{
    struct ErChaShuJieDian *pErChaShu = NULL;
    struct DuiLieJieDian *pNow = NULL;

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

void ruZhan(struct ErChaShuJieDian *pErChaShu)
{
    struct ZhanJieDian *pTemp = (struct ZhanJieDian *)malloc(sizeof(struct ZhanJieDian));

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

struct ErChaShuJieDian *chuZhan()
{
    struct ErChaShuJieDian *pErChaShu = NULL;
    struct ZhanJieDian *pNow = NULL;

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