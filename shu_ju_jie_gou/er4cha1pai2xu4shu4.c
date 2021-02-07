#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*#####二叉排序树#####*/

// 二叉树结点
typedef struct ErChaShuJieDian
{
    // 结点数值，约定都大于0
    int iShuZhi;
    // 左结点
    struct ErChaShuJieDian *pZuo;
    // 右结点
    struct ErChaShuJieDian *pYou;
} ECSJD;

// 头指针
ECSJD *pErChaShuHead = NULL;
// 定位指针，用于插入
ECSJD *pDingWei = NULL;
// 定位指针，用于删除
ECSJD *pMuBiaoFu = NULL;

// 输出数组
extern void shuChuShuZu(int *, int);
// 遍历查找
extern ECSJD *bianLiChaZhao(ECSJD *, int);
// 插入结点
extern void chaRuJieDian(int);
// 删除结点
extern void shanChuJieDian(int);
// 前序遍历
extern void qianXuBianLi(ECSJD *);
// 中序遍历
extern void zhongXuBianLi(ECSJD *);

/*#####实现代码#####*/

int main()
{
    int iArrDaiPaiXu[10];
    int iDaiPaiXuLen = 10;
    srand(time(NULL));
    for (int i = 0; i < iDaiPaiXuLen; i++)
    {
        int iChaRuZhi = rand() % 100;
        iArrDaiPaiXu[i] = iChaRuZhi;
        chaRuJieDian(iChaRuZhi);
    }

    printf("pai2xu4qian2:");
    shuChuShuZu(&iArrDaiPaiXu, iDaiPaiXuLen);

    printf("qian2xu4bian4li4:");
    qianXuBianLi(pErChaShuHead);
    printf("\n");

    printf("zhong1xu4bian4li4:");
    zhongXuBianLi(pErChaShuHead);
    printf("\n");

    shanChuJieDian(iArrDaiPaiXu[4]);

    printf("zhong1xu4bian4li4:");
    zhongXuBianLi(pErChaShuHead);
    printf("\n");
}

ECSJD *bianLiChaZhao(ECSJD *pChaXunZhiZhen, int iChaZhaoZhi)
{
    ECSJD *pTemp = NULL;

    if (pChaXunZhiZhen == NULL)
    {
        return pTemp;
    }
    // 定位指针，记录查询过程中最后一次遍历的有效的结点
    pDingWei = pChaXunZhiZhen;
    if (iChaZhaoZhi > pChaXunZhiZhen->iShuZhi)
    {
        // 查找值大，访问右子树
        pMuBiaoFu = pChaXunZhiZhen;

        return bianLiChaZhao(pChaXunZhiZhen->pYou, iChaZhaoZhi);
    }
    else if (iChaZhaoZhi < pChaXunZhiZhen->iShuZhi)
    {
        // 查找值小，访问左子树
        pMuBiaoFu = pChaXunZhiZhen;

        return bianLiChaZhao(pChaXunZhiZhen->pZuo, iChaZhaoZhi);
    }
    else
    {
        // 找到，则返回当前位置指针
        return pChaXunZhiZhen;
    }
}

void chaRuJieDian(int iChaRuZhi)
{
    ECSJD *pTemp = NULL;

    if (pErChaShuHead == NULL)
    {
        pErChaShuHead = (ECSJD *)malloc(sizeof(ECSJD));
        pErChaShuHead->iShuZhi = iChaRuZhi;
        pErChaShuHead->pZuo = NULL;
        pErChaShuHead->pYou = NULL;
    }
    else
    {
        // 重置查询指针的位置，用于插入结点
        pDingWei = NULL;
        pTemp = bianLiChaZhao(pErChaShuHead, iChaRuZhi);
        // 在查询之后，如果要插入的值已经存在，查询指针会指向查询到的结点
        // 如果要插入的值不存在，查询指针会指向将要插入结点的父结点
        if (pTemp == NULL)
        {
            pTemp = (ECSJD *)malloc(sizeof(ECSJD));
            pTemp->iShuZhi = iChaRuZhi;
            pTemp->pZuo = NULL;
            pTemp->pYou = NULL;
            // 比较一下结点应该插到哪一边
            if (iChaRuZhi > pDingWei->iShuZhi)
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

void shanChuJieDian(int iShanChuZhi)
{
    ECSJD *pMuBiao = NULL;
    ECSJD *pQianQu = NULL;
    ECSJD *pTiHuan = NULL;
    int iTag = 0;

    if (pErChaShuHead == NULL)
    {
        return;
    }
    // 找到要删除的结点的位置
    pMuBiaoFu = NULL;
    pMuBiao = bianLiChaZhao(pErChaShuHead, iShanChuZhi);
    printf("shan1chu2jie2dian3;", pMuBiaoFu->iShuZhi);
    printf("mu4biao1fu4:%d;", pMuBiaoFu->iShuZhi);
    printf("mu4biao1:%d\n", pMuBiao->iShuZhi);
    if (pMuBiao == NULL)
    {
        // 没找到
        return;
    }
    else
    {
        // 判断目标结点是父结点的哪个结点
        if (pMuBiaoFu->pZuo == pMuBiao)
        {
            iTag = 1;
        }
        else
        {
            iTag = 2;
        }
        if (pMuBiao->pZuo == NULL)
        {
            // 如果目标结点左子树为空，直接把右子树接上来
            if (iTag == 1)
            {
                pMuBiaoFu->pZuo = pMuBiao->pYou;
            }
            else
            {
                pMuBiaoFu->pYou = pMuBiao->pYou;
            }
            // 释放资源
            free(pMuBiao);
        }
        else if (pMuBiao->pYou == NULL)
        {
            // 如果目标结点右子树为空，直接把左子树接上来
            if (iTag == 1)
            {
                pMuBiaoFu->pZuo = pMuBiao->pZuo;
            }
            else
            {
                pMuBiaoFu->pYou = pMuBiao->pZuo;
            }
            // 释放资源
            free(pMuBiao);
        }
        else
        {
            // 如果目标结点的左子树和右子树都存在
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
            pMuBiao->iShuZhi = pTiHuan->iShuZhi;
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

void shuChuShuZu(int *iArrDaiPaiXu, int iDaiPaiXuLen)
{
    for (int i = 0; i < iDaiPaiXuLen; i++)
    {
        printf("%d,", iArrDaiPaiXu[i]);
    }
    printf("\n");
}