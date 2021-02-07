#include <stdio.h>
#include <stdlib.h>

// 哈夫曼字符表的最大字符数量
#define MAX_ZI_FU_NUM 128
// 哈夫曼编码表的最大编码长度
#define MAX_BIAN_MA_LEN 64

/**
 * 哈夫曼树结点
 */
typedef struct HaFuManShuJieDian
{
    // 结点类型：0=临时结点；1=字符结点
    int iLeiXing;
    // 结点权重
    int iQuanZhong;
    // 字符
    char cZiFu;
    // 左结点指针
    struct HaFuManShuJieDian *pZuo;
    // 右结点指针
    struct HaFuManShuJieDian *pYou;
} HFMSJD;

// 哈夫曼树头指针
HFMSJD *pHaFuManShuHead = NULL;
// 哈夫曼字符表和哈夫曼编码表，两者下标对应
char cArrHafuManZiFu[MAX_ZI_FU_NUM] = {'\0'};
char cArr2HafuManBianMa[MAX_ZI_FU_NUM][MAX_BIAN_MA_LEN] = {'\0'};
// 哈夫曼字符表数量
int iHafuManZiFuNum = 0;

// 构造哈夫曼树
extern void gouZaoHaFuManShu(char *, int *);
// 构造哈夫曼编码表
extern void gouZaoHaFuManBianMaBiao(HFMSJD *, char *, int);

/*#####实现代码#####*/

int main()
{
    // 待处理字符串
    char cDaiChuLi[] = "hello world";
    // 字符数组和字符权重数组，两者下标对应
    char cArrZiFu[MAX_ZI_FU_NUM] = {'\0'};
    int iArrZiFuQuanZhong[MAX_ZI_FU_NUM] = {0};
    // 临时字符权重数组，用于统计字符权重
    int tiArrZiFuQuanZhong[MAX_ZI_FU_NUM] = {0};
    // 统计字符权重
    int iZiFuZhi;
    for (int i = 0; cDaiChuLi[i] != '\0'; i++)
    {
        // 将字符转换成ASCII码值
        iZiFuZhi = (int)cDaiChuLi[i];
        tiArrZiFuQuanZhong[iZiFuZhi]++;
    }
    for (int i = 0, j = 0; i < MAX_ZI_FU_NUM; i++)
    {
        if (tiArrZiFuQuanZhong[i] != 0)
        {
            cArrZiFu[j] = (char)i;
            iArrZiFuQuanZhong[j] = tiArrZiFuQuanZhong[i];
            j++;
        }
    }
    gouZaoHaFuManShu(cArrZiFu, iArrZiFuQuanZhong);
    char tcArrBianMa[64] = "";
    gouZaoHaFuManBianMaBiao(pHaFuManShuHead, &tcArrBianMa, 0);
    for (int i = 0; i < iHafuManZiFuNum; i++)
    {
        printf("%c:", cArrHafuManZiFu[i]);
        for (int j = 0; cArr2HafuManBianMa[i][j] != '\0'; j++)
        {
            printf("%c", cArr2HafuManBianMa[i][j]);
        }
        printf("\n");
    }
    return 0;
}

void gouZaoHaFuManShu(char *cArrZiFu, int *iArrZiFuQuanZhong)
{
    // 保存所有的字符结点的指针数组
    HFMSJD *tpArrShuJieDian[MAX_ZI_FU_NUM] = {NULL};
    // 临时结点指针
    HFMSJD *tpJieDian1 = NULL;
    HFMSJD *tpJieDian2 = NULL;
    HFMSJD *tpJieDian3 = NULL;
    // 临时结点指针在指针数组中的下标
    int iTPJieDianXiaBiao1 = -1;
    int iTPJieDianXiaBiao2 = -1;
    // 创建所有的字符结点
    for (int i = 0, j = 0; i < MAX_ZI_FU_NUM; i++)
    {
        if (cArrZiFu[i] != '\0')
        {
            tpArrShuJieDian[j] = (HFMSJD *)malloc(sizeof(HFMSJD));
            tpArrShuJieDian[j]->iLeiXing = 1;
            tpArrShuJieDian[j]->iQuanZhong = iArrZiFuQuanZhong[i];
            tpArrShuJieDian[j]->cZiFu = cArrZiFu[i];
            tpArrShuJieDian[j]->pZuo = NULL;
            tpArrShuJieDian[j]->pYou = NULL;
            j++;
        }
    }
    while (1)
    {
        tpJieDian1 = NULL;
        tpJieDian2 = NULL;
        // 查找指针数组中结点权重最小的两个结点
        for (int i = 0; i < MAX_ZI_FU_NUM; i++)
        {
            if (tpArrShuJieDian[i] == NULL)
            {
                continue;
            }
            if (tpJieDian1 == NULL)
            {
                iTPJieDianXiaBiao1 = i;
                tpJieDian1 = tpArrShuJieDian[i];
            }
            else if (tpJieDian2 == NULL)
            {
                iTPJieDianXiaBiao2 = i;
                tpJieDian2 = tpArrShuJieDian[i];
            }
            else
            {
                if (tpArrShuJieDian[i]->iQuanZhong < tpJieDian1->iQuanZhong)
                {
                    iTPJieDianXiaBiao1 = i;
                    tpJieDian1 = tpArrShuJieDian[i];
                }
                else if (tpArrShuJieDian[i]->iQuanZhong < tpJieDian2->iQuanZhong)
                {
                    iTPJieDianXiaBiao2 = i;
                    tpJieDian2 = tpArrShuJieDian[i];
                }
            }
        }
        if (tpJieDian1 != NULL && tpJieDian2 != NULL)
        {
            // 如果能找到两个结点，就以这两个结点作为子结点构造一个父结点
            tpJieDian3 = (HFMSJD *)malloc(sizeof(HFMSJD));
            tpJieDian3->iLeiXing = 0;
            tpJieDian3->iQuanZhong = tpJieDian1->iQuanZhong + tpJieDian2->iQuanZhong;
            tpJieDian3->cZiFu = '\0';
            tpJieDian3->pZuo = tpJieDian1;
            tpJieDian3->pYou = tpJieDian2;
            // 把原来的两个结点指针数组中移除，把新构造的结点放入指针数组
            tpArrShuJieDian[iTPJieDianXiaBiao1] = tpJieDian3;
            tpArrShuJieDian[iTPJieDianXiaBiao2] = NULL;
        }
        else
        {
            // 指针数组中只剩一个结点，那么哈夫曼树就已经构造完成了
            if (tpJieDian1 != NULL)
            {
                pHaFuManShuHead = tpJieDian1;
                break;
            }
            else
            {
                pHaFuManShuHead = tpJieDian2;
                break;
            }
        }
    }
}

void gouZaoHaFuManBianMaBiao(HFMSJD *pNow, char *pcArrBianMa, int iBianMalen)
{
    // 构造临时编码数组，拷贝上次递归传递进来的编码数组
    char tcArrBianMa[64] = {'\0'};
    for (int i = 0; pcArrBianMa[i] != '\0'; i++)
    {
        tcArrBianMa[i] = pcArrBianMa[i];
    }
    if (pNow->iLeiXing == 0)
    {
        // 如果是临时结点就继续递归
        if (pNow->pZuo != NULL)
        {
            int iLen1 = iBianMalen;
            tcArrBianMa[iLen1] = '0';
            iLen1++;
            gouZaoHaFuManBianMaBiao(pNow->pZuo, tcArrBianMa, iLen1);
        }
        if (pNow->pYou != NULL)
        {
            int iLen2 = iBianMalen;
            tcArrBianMa[iLen2] = '1';
            iLen2++;
            gouZaoHaFuManBianMaBiao(pNow->pYou, tcArrBianMa, iLen2);
        }
    }
    else
    {
        // 如果是字符结点，那么该字符就完成了编码
        cArrHafuManZiFu[iHafuManZiFuNum] = pNow->cZiFu;
        for (int i = 0; i < iBianMalen; i++)
        {
            cArr2HafuManBianMa[iHafuManZiFuNum][i] = tcArrBianMa[i];
        }
        iHafuManZiFuNum++;
    }
}