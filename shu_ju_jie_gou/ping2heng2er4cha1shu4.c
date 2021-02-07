#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

/**
 * 二叉树结点
 */
struct ErChaShuJieDian
{
    // 数据域，约定结点值都大于0
    int num;
    // 左结点指针
    struct ErChaShuJieDian *pZuo;
    // 右结点指针
    struct ErChaShuJieDian *pYou;
    // 父结点指针
    struct ErChaShuJieDian *pFu;
    // 结点深度
    // 从下往上依次增加，最下层叶子结点的深度约定为1。
    int jieDianShenDu;
    // 平衡参数
    // 左右子树深度的差值。如果算出来是[-1,0,1]，就是平衡的。
    int pingHengCanShu;
};

// 头指针
struct ErChaShuJieDian *pErChaShuHead = NULL;

extern void chaRuJieDian(struct ErChaShuJieDian **, int);
extern int jiSuanPingHengCanShu(struct ErChaShuJieDian *);
extern void zuoXuan(struct ErChaShuJieDian *);
extern void youXuan(struct ErChaShuJieDian *);

extern void qianXuBianLi(struct ErChaShuJieDian *);
extern void zhongXuBianLi(struct ErChaShuJieDian *);
extern void shuChuXuLie(int *, int);

/**
 * 平衡二叉树
 * 平衡二叉树是一种特殊的二叉排序树
 */
int main()
{
    int daiPaiXuArr[10];
    int daiPaiXuLen = 10;
    srand(time(NULL));
    for (int i = 0; i < daiPaiXuLen; i++)
    {
        int chaRuZhi = (rand() % 99) + 1;
        daiPaiXuArr[i] = chaRuZhi;
        chaRuJieDian(&pErChaShuHead, daiPaiXuArr[i]);
    }

    printf("pai2xu4qian2:");
    shuChuXuLie(&daiPaiXuArr, daiPaiXuLen);

    printf("qian2xu4bian4li4:");
    qianXuBianLi(pErChaShuHead);
    printf("\n");

    printf("zhong1xu4bian4li4:");
    zhongXuBianLi(pErChaShuHead);
    printf("\n");
}

/**
 * 插入结点
 */
void chaRuJieDian(struct ErChaShuJieDian **ppNow, int chaRuZhi)
{
    if (*ppNow == NULL)
    {
        // 头指针为空
        *ppNow = (struct ErChaShuJieDian *)malloc(sizeof(struct ErChaShuJieDian));
        if (*ppNow == NULL)
        {
            printf("nei4cun2fen1pei4shi1bai4!\n");
            exit(0);
        }
        (*ppNow)->num = chaRuZhi;
        (*ppNow)->pZuo = NULL;
        (*ppNow)->pYou = NULL;
        (*ppNow)->pFu = NULL;
        (*ppNow)->jieDianShenDu = 1;
        (*ppNow)->pingHengCanShu = 0;
    }
    else
    {
        if (chaRuZhi < (*ppNow)->num)
        {
            if ((*ppNow)->pZuo != NULL)
            {
                chaRuJieDian(&((*ppNow)->pZuo), chaRuZhi);
            }
            else
            {
                (*ppNow)->pZuo = (struct ErChaShuJieDian *)malloc(sizeof(struct ErChaShuJieDian));
                if ((*ppNow)->pZuo == NULL)
                {
                    printf("nei4cun2fen1pei4shi1bai4!\n");
                    exit(0);
                }
                (*ppNow)->pZuo->num = chaRuZhi;
                (*ppNow)->pZuo->pZuo = NULL;
                (*ppNow)->pZuo->pYou = NULL;
                (*ppNow)->pZuo->pFu = *ppNow;
                (*ppNow)->pZuo->jieDianShenDu = 1;
                (*ppNow)->pZuo->pingHengCanShu = 0;
            }
        }
        else if (chaRuZhi > (*ppNow)->num)
        {
            if ((*ppNow)->pYou != NULL)
            {
                chaRuJieDian(&((*ppNow)->pYou), chaRuZhi);
            }
            else
            {
                (*ppNow)->pYou = (struct ErChaShuJieDian *)malloc(sizeof(struct ErChaShuJieDian));
                if ((*ppNow)->pYou == NULL)
                {
                    printf("nei4cun2fen1pei4shi1bai4!\n");
                    exit(0);
                }
                (*ppNow)->pYou->num = chaRuZhi;
                (*ppNow)->pYou->pZuo = NULL;
                (*ppNow)->pYou->pYou = NULL;
                (*ppNow)->pYou->pFu = *ppNow;
                (*ppNow)->pYou->jieDianShenDu = 1;
                (*ppNow)->pYou->pingHengCanShu = 0;
            }
        }
        // 检查是否需要旋转
        (*ppNow)->pingHengCanShu = jiSuanPingHengCanShu(*ppNow);
        if ((*ppNow)->pingHengCanShu > 1)
        {
            // 左子树高，LL型
            if ((*ppNow)->pZuo->pingHengCanShu == -1)
            {
                // 左子树的右子树高，LR型
                zuoXuan((*ppNow)->pZuo);
            }
            youXuan(*ppNow);
        }
        if ((*ppNow)->pingHengCanShu < -1)
        {
            // 右子树高，RR型
            if ((*ppNow)->pYou->pingHengCanShu == 1)
            {
                // 右子树的左子树高，RL型
                youXuan((*ppNow)->pYou);
            }
            zuoXuan(*ppNow);
        }
        // 计算深度和平衡参数
        (*ppNow)->jieDianShenDu = jiSuanShenDu(*ppNow);
        (*ppNow)->pingHengCanShu = jiSuanPingHengCanShu(*ppNow);
    }
}

/**
 * 计算结点深度
 * 结点深度=左右子树中深度更大的子树那个子树的深度+1
 */
int jiSuanShenDu(struct ErChaShuJieDian *pNow)
{
    int zuoShenDu = 0;
    int youShenDu = 0;
    if (pNow->pZuo != NULL)
    {
        zuoShenDu = pNow->pZuo->jieDianShenDu;
    }
    if (pNow->pYou != NULL)
    {
        youShenDu = pNow->pYou->jieDianShenDu;
    }
    return (int)fmax(zuoShenDu, youShenDu) + 1;
}

/**
 * 计算结点平衡参数
 * 结点平衡参数=左子树深度-右子树深度
 */
int jiSuanPingHengCanShu(struct ErChaShuJieDian *pNow)
{
    int zuoShenDu = 0;
    int youShenDu = 0;
    if (pNow->pZuo != NULL)
    {
        zuoShenDu = pNow->pZuo->jieDianShenDu;
    }
    if (pNow->pYou != NULL)
    {
        youShenDu = pNow->pYou->jieDianShenDu;
    }
    return zuoShenDu - youShenDu;
}

/**
 * 左旋，自己的右结点变自己的父结点
 */
void zuoXuan(struct ErChaShuJieDian *pNow)
{
    // 自己的父结点指针
    struct ErChaShuJieDian *pTFu = pNow->pFu;
    // 自己的右结点指针
    struct ErChaShuJieDian *pTYou = pNow->pYou;
    // 自己的右结点的左结点指针
    struct ErChaShuJieDian *pTYouZuo = pTYou->pZuo;
    if (pNow == pErChaShuHead)
    {
        // 自己是根结点
        pErChaShuHead = pNow->pYou;
    }
    // 交换两个结点的位置
    pTYou->pFu = pTFu;
    pTYou->pZuo = pNow;
    pNow->pFu = pTYou;
    if (pTFu != NULL)
    {
        // 如果自己有父结点
        // 要把左旋上去的自己的右结点接到父结点相应的位置
        if (pNow == pTFu->pZuo)
        {
            pTFu->pZuo = pTYou;
        }
        else if (pNow == pTFu->pYou)
        {
            pTFu->pYou = pTYou;
        }
    }
    // 如果自己的右结点有左结点，要把这个左结点变成自己的右结点
    pNow->pYou = pTYouZuo;
    if (pTYouZuo != NULL)
    {
        pTYouZuo->pFu = pNow;
    }
    // 重新计算参与旋转的两个结点的深度和平衡参数
    pNow->jieDianShenDu = jiSuanShenDu(pNow);
    pNow->pingHengCanShu = jiSuanPingHengCanShu(pNow);
    pTYou->jieDianShenDu = jiSuanShenDu(pTYou);
    pTYou->pingHengCanShu = jiSuanPingHengCanShu(pTYou);
}

/**
 * 右旋，自己的左结点变自己的父结点
 */
void youXuan(struct ErChaShuJieDian *pNow)
{
    // 自己的父结点指针
    struct ErChaShuJieDian *pTFu = pNow->pFu;
    // 自己的左结点指针
    struct ErChaShuJieDian *pTZuo = pNow->pZuo;
    // 自己的左结点的右结点指针
    struct ErChaShuJieDian *pTZuoYou = pTZuo->pYou;
    if (pNow == pErChaShuHead)
    {
        pErChaShuHead = pTZuo;
    }
    pTZuo->pFu = pTFu;
    pTZuo->pYou = pNow;
    pNow->pFu = pTZuo;
    if (pTFu != NULL)
    {
        // 如果自己有父结点
        // 要把右旋上去的自己的左结点接到父结点相应的位置
        if (pNow == pTFu->pZuo)
        {
            pTFu->pZuo = pTZuo;
        }
        else if (pNow == pTFu->pYou)
        {
            pTFu->pYou = pTZuo;
        }
    }
    // 如果自己的左结点有右结点，要把这个右结点变成自己的左结点
    pNow->pZuo = pTZuoYou;
    if (pTZuoYou != NULL)
    {
        pTZuoYou->pFu = pNow;
    }
    pNow->jieDianShenDu = jiSuanShenDu(pNow);
    pNow->pingHengCanShu = jiSuanPingHengCanShu(pNow);
    pTZuo->jieDianShenDu = jiSuanShenDu(pTZuo);
    pTZuo->pingHengCanShu = jiSuanPingHengCanShu(pTZuo);
}

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

void shuChuXuLie(int *daiPaiXuArr, int daiPaiXuLen)
{
    for (int i = 0; i < daiPaiXuLen; i++)
    {
        printf("%d,", daiPaiXuArr[i]);
    }
    printf("\n");
}