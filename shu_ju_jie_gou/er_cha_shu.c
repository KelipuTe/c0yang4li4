#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*#####二叉树#####*/

/**
 * 二叉树节点
 */
struct ErChaShuJieDian
{
    int num;
    struct ErChaShuJieDian *pZuo;
    struct ErChaShuJieDian *pYou;
    int cengShu;
};

// 头指针
struct ErChaShuJieDian *pErChaShuHead;

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

struct DuiLieJieDian *pDuiLieHead;
struct DuiLieJieDian *pDuiLieTail;

extern void chuShiHuaDuiLie();
extern void ruDui(struct ErChaShuJieDian *, int);
extern struct ErChaShuJieDian *chuDui();

/*#####栈#####*/

struct ZhanJieDian
{
    struct ErChaShuJieDian *pErChaShu;
    struct ZhanJieDian *pNext;
};

struct ZhanJieDian *pZhanDing;

extern void chuShiHuaZhan();
extern void ruZhan(struct ErChaShuJieDian *);
extern struct ErChaShuJieDian *chuZhan();

int main()
{
    int yuanSuBiao[] = {1, 2, 3, 4, 5, 6, 7, 0, 0, 10, 11};
    int yuanSuBiaoLen = sizeof(yuanSuBiao) / sizeof(int);
    chuShiHuaErChaShu();
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
    printf("er4cha1shu4shen1du4:%d\n", jiSuanErChaShuShenDu(pErChaShuHead));
    printf("guang3du4you1xian1bian4li4:");
    guangDuYouXianBianLi();
    printf("\n");
    printf("shen1du4you1xian1bian4li4:");
    shenDuYouXianBianLi();
    printf("\n");
}

/*#####二叉树#####*/

/**
 * 初始化
 */
void chuShiHuaErChaShu()
{
    pErChaShuHead = NULL;
}

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
            struct ErChaShuJieDian *pTemp = (struct ErChaShuJieDian *)malloc(sizeof(struct ErChaShuJieDian));
            *pNow = pTemp;
            if (*pNow == NULL)
            {
                printf("nei4cun2fen1pei4shi1bai4!\n");
                exit(0);
            }
            (*pNow)->num = yuanSuBiao[index - 1];
            (*pNow)->pZuo = NULL;
            (*pNow)->pYou = NULL;
            (*pNow)->cengShu = 0;
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
    if (pNow == NULL)
    {
        return 0;
    }
    int zuoShenDu = jiSuanErChaShuShenDu(pNow->pZuo);
    int youShenDu = jiSuanErChaShuShenDu(pNow->pYou);
    return (int)fmax(zuoShenDu, youShenDu) + 1;
}

/**
 * 广度优先遍历
 */
void guangDuYouXianBianLi()
{
    int cengShu = 1;
    ruDui(pErChaShuHead, cengShu);
    struct ErChaShuJieDian *pErChaShu;
    pErChaShu = chuDui();
    while (pErChaShu != NULL)
    {
        // 持续遍历，直到队列为空
        printf("%d-%d,", pErChaShu->cengShu, pErChaShu->num);
        if (pErChaShu->pZuo != NULL)
        {
            // 左结点先入队，先遍历
            ruDui(pErChaShu->pZuo, pErChaShu->cengShu + 1);
        }
        if (pErChaShu->pYou != NULL)
        {
            // 右结点后入队，后遍历
            ruDui(pErChaShu->pYou, pErChaShu->cengShu + 1);
        }
        pErChaShu = chuDui();
    }
}

/**
 * 深度优先遍历
 */
void shenDuYouXianBianLi()
{
    ruZhan(pErChaShuHead);
    struct ErChaShuJieDian *pErChaShu;
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

void chuShiHuaDuiLie()
{
    pDuiLieHead = NULL;
    pDuiLieTail = NULL;
}

void ruDui(struct ErChaShuJieDian *pErChaShu, int cengShu)
{
    struct DuiLieJieDian *pTemp = (struct DuiLieJieDian *)malloc(sizeof(struct DuiLieJieDian));
    // 入队时记录层数
    pErChaShu->cengShu = cengShu;
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
    if (pDuiLieHead == NULL)
    {
        return pErChaShu;
    }
    struct DuiLieJieDian *pNow = pDuiLieHead;
    pErChaShu = pDuiLieHead->pErChaShu;
    pDuiLieHead = pDuiLieHead->pNext;
    free(pNow);
    return pErChaShu;
}

/*#####栈#####*/

void chuShiHuaZhan()
{
    pZhanDing = NULL;
}

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
    if (pZhanDing == NULL)
    {
        return pErChaShu;
    }
    struct ZhanJieDian *pNow = pZhanDing;
    pErChaShu = pZhanDing->pErChaShu;
    pZhanDing = pZhanDing->pNext;
    free(pNow);
    return pErChaShu;
}