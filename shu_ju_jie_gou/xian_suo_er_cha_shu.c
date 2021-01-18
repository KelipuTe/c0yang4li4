#include <stdio.h>
#include <stdlib.h>

/**
 * 二叉树结点
 */
struct ErChaShuJieDian
{
    // 结点值，约定结点值都大于0
    int num;
    // 左标识:-1=未设置；0=前驱；1=左结点
    int zuoBiaoShi;
    // 左结点
    struct ErChaShuJieDian *pZuo;
    // 右标识:-1=未设置；0=后继；1=右结点
    int youBiaoShi;
    // 右结点
    struct ErChaShuJieDian *pYou;
};

// 头指针
struct ErChaShuJieDian *pErChaShuHead = NULL;
// 前驱结点指针
struct ErChaShuJieDian *pQianQu = NULL;

extern void gouZaoErChaShu(struct ErChaShuJieDian **, int *, int, int, struct ErChaShuJieDian *);
extern void zhongXuBianLiXianSuoHua(struct ErChaShuJieDian *);
extern void qianXuBianLi(struct ErChaShuJieDian *);
extern void zhongXuBianLi(struct ErChaShuJieDian *);

/**
 * 线索二叉树
 */
int main()
{
    int yuanSuBiao[] = {1, 2, 3, 0, 5, 0, 7, 0, 0, 10, 11, 0, 0, 14};
    int yuanSuBiaoLen = sizeof(yuanSuBiao) / sizeof(int);
    gouZaoErChaShu(&pErChaShuHead, &yuanSuBiao, yuanSuBiaoLen, 1, NULL);
    zhongXuBianLiXianSuoHua(pErChaShuHead);

    printf("qian2xu4bian4li4:");
    qianXuBianLi(pErChaShuHead);
    printf("\n");

    printf("zhong1xu4bian4li4:");
    zhongXuBianLi(pErChaShuHead);
    printf("\n");
}

void gouZaoErChaShu(struct ErChaShuJieDian **ppNow, int *yuanSuBiao, int yuanSuBiaoLen, int index, struct ErChaShuJieDian *pFu)
{
    if (index <= yuanSuBiaoLen)
    {
        if (yuanSuBiao[index - 1] == 0)
        {
            *ppNow = NULL;

            return;
        }
        else
        {
            *ppNow = (struct ErChaShuJieDian *)malloc(sizeof(struct ErChaShuJieDian));
            if (*ppNow == NULL)
            {
                printf("nei4cun2fen1pei4shi1bai4!\n");
                exit(0);
            }
            (*ppNow)->num = yuanSuBiao[index - 1];
            (*ppNow)->zuoBiaoShi = -1;
            (*ppNow)->pZuo = NULL;
            (*ppNow)->youBiaoShi = -1;
            (*ppNow)->pYou = NULL;
            if (pFu != NULL)
            {
                if (pFu->pZuo == *ppNow)
                {
                    pFu->zuoBiaoShi = 1;
                }
                else if (pFu->pYou == *ppNow)
                {
                    pFu->youBiaoShi = 1;
                }
            }
            gouZaoErChaShu(&((*ppNow)->pZuo), yuanSuBiao, yuanSuBiaoLen, index * 2, *ppNow);
            gouZaoErChaShu(&((*ppNow)->pYou), yuanSuBiao, yuanSuBiaoLen, index * 2 + 1, *ppNow);
        }
    }
}

void qianXuBianLi(struct ErChaShuJieDian *pNow)
{
    if (pNow == NULL)
    {
        return;
    }
    printf("%d,", pNow->num);
    if (pNow->zuoBiaoShi == 1)
    {
        qianXuBianLi(pNow->pZuo);
    }
    if (pNow->youBiaoShi == 1)
    {
        qianXuBianLi(pNow->pYou);
    }
}

void zhongXuBianLi(struct ErChaShuJieDian *pNow)
{
    if (pNow == NULL)
    {
        return;
    }
    if (pNow->zuoBiaoShi == 1)
    {
        zhongXuBianLi(pNow->pZuo);
    }
    printf("%d,", pNow->num);
    if (pNow->youBiaoShi == 1)
    {
        zhongXuBianLi(pNow->pYou);
    }
}

/**
 * 中序遍历线索化
 */
void zhongXuBianLiXianSuoHua(struct ErChaShuJieDian *pNow)
{
    if (pNow == NULL)
    {
        return;
    }
    // 处理左结点
    if (pNow->zuoBiaoShi == 1)
    {
        // 有左结点
        zhongXuBianLiXianSuoHua(pNow->pZuo);
    }
    else if (pNow->zuoBiaoShi == -1)
    {
        // 没设置左结点
        if (pQianQu != NULL)
        {
            pNow->zuoBiaoShi = 0;
            pNow->pZuo = pQianQu;
        }
    }
    // 判断前驱结点有没有设置过后继结点
    if (pQianQu != NULL && pQianQu->youBiaoShi == -1)
    {
        pQianQu->youBiaoShi = 0;
        pQianQu->pYou = pNow;
    }
    // 登记自己为新的前驱结点
    pQianQu = pNow;
    // 处理右结点
    if (pNow->youBiaoShi == 1)
    {
        // 有右节点
        zhongXuBianLiXianSuoHua(pNow->pYou);
    }
}