#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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
};

// 头指针
struct ErChaShuJieDian *pErChaShuHead = NULL;
// 定位指针，用于插入
struct ErChaShuJieDian *pDingWei = NULL;
// 定位指针，用于删除
struct ErChaShuJieDian *pMuBiaoFu = NULL;

extern struct ErChaShuJieDian *bianLiChaZhao(struct ErChaShuJieDian *, int);
extern void chaRuJieDian(int);
extern void shanChuJieDian(int);

extern void qianXuBianLi(struct ErChaShuJieDian *);
extern void zhongXuBianLi(struct ErChaShuJieDian *);
extern void shuChuXuLie(int *, int);

/**
 * 二叉排序树
 */
int main()
{
    int daiPaiXuArr[10];
    int daiPaiXuLen = 10;
    srand(time(NULL));
    for (int i = 0; i < daiPaiXuLen; i++)
    {
        int chaRuZhi = rand() % 100;
        daiPaiXuArr[i] = chaRuZhi;
        chaRuJieDian(chaRuZhi);
    }

    printf("pai2xu4qian2:");
    shuChuXuLie(&daiPaiXuArr, daiPaiXuLen);

    shanChuJieDian(daiPaiXuArr[4]);

    printf("qian2xu4bian4li4:");
    qianXuBianLi(pErChaShuHead);
    printf("\n");

    printf("zhong1xu4bian4li4:");
    zhongXuBianLi(pErChaShuHead);
    printf("\n");
}

/**
 * 遍历查找
 */
struct ErChaShuJieDian *bianLiChaZhao(struct ErChaShuJieDian *chaXunZhiZhen, int chaZhaoZhi)
{
    struct ErChaShuJieDian *pTemp = NULL;

    if (chaXunZhiZhen == NULL)
    {
        return pTemp;
    }
    // 定位指针，记录查询过程中最后一次遍历的有效的结点
    pDingWei = chaXunZhiZhen;
    if (chaZhaoZhi > chaXunZhiZhen->num)
    {
        // 查找值大，访问右子树
        pMuBiaoFu = chaXunZhiZhen;
        return bianLiChaZhao(chaXunZhiZhen->pYou, chaZhaoZhi);
    }
    else if (chaZhaoZhi < chaXunZhiZhen->num)
    {
        // 查找值小，访问左子树
        pMuBiaoFu = chaXunZhiZhen;
        return bianLiChaZhao(chaXunZhiZhen->pZuo, chaZhaoZhi);
    }
    else
    {
        // 找到，则返回当前位置指针
        return chaXunZhiZhen;
    }
}

/**
 * 插入结点
 */
void chaRuJieDian(int chaRuZhi)
{
    struct ErChaShuJieDian *pTemp = NULL;

    if (pErChaShuHead == NULL)
    {
        pErChaShuHead = (struct ErChaShuJieDian *)malloc(sizeof(struct ErChaShuJieDian));
        pErChaShuHead->num = chaRuZhi;
        pErChaShuHead->pZuo = NULL;
        pErChaShuHead->pYou = NULL;
    }
    else
    {
        // 重置查询指针的位置，用于插入结点
        pDingWei = NULL;
        pTemp = bianLiChaZhao(pErChaShuHead, chaRuZhi);
        // 在查询之后，如果要插入的值已经存在，查询指针会指向查询到的结点
        // 如果要插入的值不存在，查询指针会指向将要插入结点的父结点
        if (pTemp == NULL)
        {
            pTemp = (struct ErChaShuJieDian *)malloc(sizeof(struct ErChaShuJieDian));
            pTemp->num = chaRuZhi;
            pTemp->pZuo = NULL;
            pTemp->pYou = NULL;
            // 比较一下插入结点应该插到哪一边
            if (chaRuZhi > pDingWei->num)
            {
                pDingWei->pYou = pTemp;
            }
            else
            {
                pDingWei->pZuo = pTemp;
            }
        }
    }
}

/**
 * 删除结点
 */
void shanChuJieDian(int shanChuZhi)
{
    struct ErChaShuJieDian *pMuBiao = NULL;
    struct ErChaShuJieDian *pQianQu = NULL;
    struct ErChaShuJieDian *pTiHuan = NULL;
    int tag = 0;

    if (pErChaShuHead == NULL)
    {
        return;
    }
    // 找到要删除的结点的位置
    pMuBiaoFu = NULL;
    pMuBiao = bianLiChaZhao(pErChaShuHead, shanChuZhi);
    printf("%d", pMuBiaoFu->num);
    printf("%d", pMuBiao->num);
    if (pMuBiao == NULL)
    {
        return;
    }
    else
    {
        if (pMuBiaoFu->pZuo == pMuBiao)
        {
            tag = 1;
        }
        else
        {
            tag = 2;
        }

        if (pMuBiao->pZuo == NULL)
        {
            // 如果左子树为空，直接把右子树接上来
            if (tag == 1)
            {
                pMuBiaoFu->pZuo = pMuBiao->pYou;
            }
            else
            {
                pMuBiaoFu->pYou = pMuBiao->pYou;
            }
            free(pMuBiao);
        }
        else if (pMuBiao->pYou == NULL)
        {
            // 如果右子树为空，直接把左子树接上来
            if (tag == 1)
            {
                pMuBiaoFu->pZuo = pMuBiao->pZuo;
            }
            else
            {
                pMuBiaoFu->pYou = pMuBiao->pZuo;
            }
            free(pMuBiao);
        }
        else
        {
            // 如果左子树和右子树都存在
            // 这里的办法是从左子树中找到结点值最大的结点替代被删除的结点
            // 同理，从右子树中找到结点值最小的结点也是可行的
            pQianQu = pMuBiao;
            pTiHuan = pQianQu->pZuo;
            while (pTiHuan->pYou != NULL)
            {
                pQianQu = pTiHuan;
                pTiHuan = pTiHuan->pYou;
            }
            // 直接把结点值最大的结点的结点值赋值到要删除的结点上
            pMuBiao->num = pTiHuan->num;
            if (pQianQu != pMuBiao)
            {
                // 如果替代结点的前驱结点不是删除结点的位置
                // 则删除结点左结点有右结点，需要考虑该右结点的左子树
                pQianQu->pYou = pTiHuan->pZuo;
            }
            else
            {
                // 如果替代结点的前驱结点就是删除结点的位置
                // 则删除结点左结点没有右结点，直接把该左结点的左子树接过来
                pQianQu->pZuo = pTiHuan->pZuo;
            }
            // 释放掉结点值最大的结点，因为这个结点的值已经被记录到原先要删除的结点了
            free(pTiHuan);
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