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
    int leiXing;
    // 结点权重
    int quanZhong;
    // 字符
    char ziFu;
    // 左结点指针
    struct HaFuManShuJieDian *pZuo;
    // 右结点指针
    struct HaFuManShuJieDian *pYou;
} HFMSJD;

// 哈夫曼树头指针
struct HaFuManShuJieDian *pHaFuManShuHead = NULL;
// 哈夫曼字符表和哈夫曼编码表，两者下标对应
char arrHafuManZiFu[MAX_ZI_FU_NUM] = {'\0'};
char arrHafuManBianMa[MAX_ZI_FU_NUM][MAX_BIAN_MA_LEN] = {'\0'};
// 哈夫曼字符表数量
int iHafuManZiFuNum = 0;

extern void gouZaoHaFuManShu(char *, int *);
extern void gouZaoHaFuManBianMaBiao(HFMSJD *, char *, int);

/**
 * 哈夫曼树
 */
int main()
{
    // 待处理字符串
    char sDaiChuLi[] = "hello world";
    // 字符数组和字符权重数组，两者下标对应
    char arrZiFu[MAX_ZI_FU_NUM] = {'\0'};
    int arrZiFuQuanZhong[MAX_ZI_FU_NUM] = {0};
    // 临时字符权重数组，用于统计字符权重
    int arrTZiFuQuanZhong[MAX_ZI_FU_NUM] = {0};
    // 统计字符权重
    int iZiFuZhi;
    for (int i = 0; sDaiChuLi[i] != '\0'; i++)
    {
        // 将字符转换成ASCII码值
        iZiFuZhi = (int)sDaiChuLi[i];
        arrTZiFuQuanZhong[iZiFuZhi]++;
    }
    for (int i = 0, j = 0; i < MAX_ZI_FU_NUM; i++)
    {
        if (arrTZiFuQuanZhong[i] != 0)
        {
            arrZiFu[j] = (char)i;
            arrZiFuQuanZhong[j] = arrTZiFuQuanZhong[i];
            j++;
        }
    }
    gouZaoHaFuManShu(arrZiFu, arrZiFuQuanZhong);
    char arrT[64] = "";
    gouZaoHaFuManBianMaBiao(pHaFuManShuHead, arrT, 0);
    for (int i = 0; i < iHafuManZiFuNum; i++)
    {
        printf("%c:", arrHafuManZiFu[i]);
        for (int j = 0; arrHafuManBianMa[i][j] != '\0'; j++)
        {
            printf("%c", arrHafuManBianMa[i][j]);
        }
        printf("\n");
    }
    return 0;
}

/**
 * 构造哈夫曼树
 */
void gouZaoHaFuManShu(char *arrZiFu, int *arrZiFuQuanZhong)
{
    // 保存所有的字符结点的指针数组
    HFMSJD *pTArrShuJieDian[MAX_ZI_FU_NUM] = {NULL};
    // 临时结点指针
    HFMSJD *pTJieDian1 = NULL;
    HFMSJD *pTJieDian2 = NULL;
    HFMSJD *pTJieDian3 = NULL;
    // 临时结点指针在指针数组中的下标
    int pTJieDianXiaBiao1 = -1;
    int pTJieDianXiaBiao2 = -1;
    // 创建所有的字符结点
    for (int i = 0, j = 0; i < MAX_ZI_FU_NUM; i++)
    {
        if (arrZiFu[i] != '\0')
        {
            pTArrShuJieDian[j] = (HFMSJD *)malloc(sizeof(HFMSJD));
            pTArrShuJieDian[j]->leiXing = 1;
            pTArrShuJieDian[j]->quanZhong = arrZiFuQuanZhong[i];
            pTArrShuJieDian[j]->ziFu = arrZiFu[i];
            pTArrShuJieDian[j]->pZuo = NULL;
            pTArrShuJieDian[j]->pYou = NULL;
            j++;
        }
    }
    while (1)
    {
        pTJieDian1 = NULL;
        pTJieDian2 = NULL;
        // 查找指针数组中结点权重最小的两个结点
        for (int i = 0; i < MAX_ZI_FU_NUM; i++)
        {
            if (pTArrShuJieDian[i] == NULL)
            {
                continue;
            }
            if (pTJieDian1 == NULL)
            {
                pTJieDianXiaBiao1 = i;
                pTJieDian1 = pTArrShuJieDian[i];
            }
            else if (pTJieDian2 == NULL)
            {
                pTJieDianXiaBiao2 = i;
                pTJieDian2 = pTArrShuJieDian[i];
            }
            else
            {
                if (pTArrShuJieDian[i]->quanZhong < pTJieDian1->quanZhong)
                {
                    pTJieDianXiaBiao1 = i;
                    pTJieDian1 = pTArrShuJieDian[i];
                }
                else if (pTArrShuJieDian[i]->quanZhong < pTJieDian2->quanZhong)
                {
                    pTJieDianXiaBiao2 = i;
                    pTJieDian2 = pTArrShuJieDian[i];
                }
            }
        }
        if (pTJieDian1 != NULL && pTJieDian2 != NULL)
        {
            // 如果能找到两个结点，就以这两个结点作为子结点构造一个父结点
            pTJieDian3 = (HFMSJD *)malloc(sizeof(HFMSJD));
            pTJieDian3->leiXing = 0;
            pTJieDian3->quanZhong = pTJieDian1->quanZhong + pTJieDian2->quanZhong;
            pTJieDian3->ziFu = '\0';
            pTJieDian3->pZuo = pTJieDian1;
            pTJieDian3->pYou = pTJieDian2;
            // 把原来的两个结点指针数组中移除，把新构造的结点放入指针数组
            pTArrShuJieDian[pTJieDianXiaBiao1] = pTJieDian3;
            pTArrShuJieDian[pTJieDianXiaBiao2] = NULL;
        }
        else
        {
            // 指针数组中只剩一个结点，那么哈夫曼树就已经构造完成了
            if (pTJieDian1 != NULL)
            {
                pHaFuManShuHead = pTJieDian1;
                break;
            }
            else
            {
                pHaFuManShuHead = pTJieDian2;
                break;
            }
        }
    }
}

/**
 * 构造哈夫曼编码表
 */
void gouZaoHaFuManBianMaBiao(HFMSJD *pNow, char *arrBianMa, int iBianMalen)
{
    // 构造临时编码数组，拷贝上次递归传递进来的编码数组
    char arrTBianMa[64] = {'\0'};
    for (int i = 0; arrBianMa[i] != '\0'; i++)
    {
        arrTBianMa[i] = arrBianMa[i];
    }
    if (pNow->leiXing == 0)
    {
        // 如果是临时结点就继续递归
        if (pNow->pZuo != NULL)
        {
            int len1 = iBianMalen;
            arrTBianMa[len1] = '0';
            len1++;
            gouZaoHaFuManBianMaBiao(pNow->pZuo, arrTBianMa, len1);
        }
        if (pNow->pYou != NULL)
        {
            int len2 = iBianMalen;
            arrTBianMa[len2] = '1';
            len2++;
            gouZaoHaFuManBianMaBiao(pNow->pYou, arrTBianMa, len2);
        }
    }
    else
    {
        // 如果是字符结点，那么该字符就完成了编码
        arrHafuManZiFu[iHafuManZiFuNum] = pNow->ziFu;
        for (int i = 0; i < iBianMalen; i++)
        {
            arrHafuManBianMa[iHafuManZiFuNum][i] = arrTBianMa[i];
        }
        iHafuManZiFuNum++;
    }
}