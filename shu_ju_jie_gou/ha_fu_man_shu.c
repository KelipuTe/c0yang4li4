#include <stdio.h>
#include <stdlib.h>

#define MAX_CHAR_NUM 128

/**
 * 哈夫曼树结点
 */
struct HaFuManShuJieDian
{
    // 结点类型
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

// 哈弗曼树头指针
struct HaFuManShuJieDian *pHaFuManShuHead = NULL;
// 哈弗曼编码表
char HafuManBianMaBiao[MAX_CHAR_NUM][64] = {'\0'};
char HafuManBianMaBiao2[MAX_CHAR_NUM] = {'\0'};
int shuLiang = 0;
// 字符权重数组和字符数组，两者下标对应
int ziFuQuanZhongArr[MAX_CHAR_NUM] = {0};
char ziFuArr[MAX_CHAR_NUM] = {'\0'};

extern void gouZaoHaFuManShu();
extern void gouZaoHaFuManBianMaBiao();

int main()
{
    // 待处理字符串
    char daiChuLiStr[] = "hello world";
    // 临时字符权重数组，用于统计字符权重
    int tZiFuQuanZhongArr[MAX_CHAR_NUM] = {0};
    for (int i = 0; daiChuLiStr[i] != '\0'; i++)
    {
        int ziFuZhi = (int)daiChuLiStr[i];
        tZiFuQuanZhongArr[ziFuZhi]++;
    }
    for (int i = 0, j = 0; i < MAX_CHAR_NUM; i++)
    {
        if (tZiFuQuanZhongArr[i] != 0)
        {
            ziFuQuanZhongArr[j] = tZiFuQuanZhongArr[i];
            ziFuArr[j] = (char)i;
            j++;
        }
    }
    gouZaoHaFuManShu();
    char tempArr[64]="";
    gouZaoHaFuManBianMaBiao(pHaFuManShuHead, tempArr, 0);
    for(int i=0;i<shuLiang;i++){
        printf("%c:",HafuManBianMaBiao2[i]);
        for(int j=0;HafuManBianMaBiao[i][j]!='\0';j++){
            printf("%c",HafuManBianMaBiao[i][j]);
        }
        printf("\n");
    }
    return 0;
}

void gouZaoHaFuManShu()
{
    struct HaFuManShuJieDian *tPShuArr[MAX_CHAR_NUM] = {NULL};
    struct HaFuManShuJieDian *tpI1 = NULL;
    struct HaFuManShuJieDian *tpI2 = NULL;
    for (int i = 0, j = 0; i < MAX_CHAR_NUM; i++)
    {
        if (ziFuArr[i] != '\0')
        {
            tPShuArr[j] = (struct HaFuManShuJieDian *)malloc(sizeof(struct HaFuManShuJieDian));
            tPShuArr[j]->leiXing = 1;
            tPShuArr[j]->quanZhong = ziFuQuanZhongArr[i];
            tPShuArr[j]->ziFu = ziFuArr[i];
            tPShuArr[j]->pZuo = NULL;
            tPShuArr[j]->pYou = NULL;
            j++;
        }
    }
    while (1)
    {
        int weizhi1;
        int weizhi2;
        tpI1 = NULL;
        tpI2 = NULL;
        for (int i = 0; i < MAX_CHAR_NUM; i++)
        {
            if (tPShuArr[i] == NULL)
            {
                continue;
            }
            if (tpI1 == NULL)
            {
                weizhi1 = i;
                tpI1 = tPShuArr[i];
            }
            else if (tpI2 == NULL)
            {
                weizhi2 = i;
                tpI2 = tPShuArr[i];
            }
            else
            {
                if (tPShuArr[i]->quanZhong < tpI1->quanZhong)
                {
                    weizhi1 = i;
                    tpI1 = tPShuArr[i];
                }
                else if (tPShuArr[i]->quanZhong < tpI2->quanZhong)
                {
                    weizhi2 = i;
                    tpI2 = tPShuArr[i];
                }
            }
        }
        if (tpI1 != NULL && tpI2 != NULL)
        {
            struct HaFuManShuJieDian *tpI3 = (struct HaFuManShuJieDian *)malloc(sizeof(struct HaFuManShuJieDian));
            tpI3->leiXing = 0;
            tpI3->quanZhong = tpI1->quanZhong + tpI2->quanZhong;
            tpI3->ziFu = '\0';
            tpI3->pZuo = tpI1;
            tpI3->pYou = tpI2;
            tPShuArr[weizhi1] = tpI3;
            tPShuArr[weizhi2] = NULL;
        }
        else
        {
            if (tpI1 != NULL)
            {
                pHaFuManShuHead = tpI1;
                break;
            }
            else
            {
                pHaFuManShuHead = tpI2;
                break;
            }
        }
    }
}

void gouZaoHaFuManBianMaBiao(struct HaFuManShuJieDian *pNow, char *bianMa, int len)
{
    char tBianMa[64]={'\0'};
    for(int i=0;bianMa[i]!='\0';i++){
        tBianMa[i]=bianMa[i];
    }
    if (pNow->leiXing == 0)
    {
        if (pNow->pZuo != NULL)
        {
            int len1=len;
            tBianMa[len1] = '0';
            len1++;
            gouZaoHaFuManBianMaBiao(pNow->pZuo, tBianMa, len1);
        }
        if (pNow->pYou != NULL)
        {
            int len2=len;
            tBianMa[len2] = '1';
            len2++;
            gouZaoHaFuManBianMaBiao(pNow->pYou, tBianMa, len2);
        }
    }
    else
    {
        for (int i = 0; i < len; i++)
        {
            HafuManBianMaBiao[shuLiang][i] = tBianMa[i];
        }
        HafuManBianMaBiao2[shuLiang]=pNow->ziFu;
        shuLiang++;
    }
}