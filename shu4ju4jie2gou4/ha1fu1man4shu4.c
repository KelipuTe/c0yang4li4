#include <stdio.h>
#include <stdlib.h>

/*#####哈夫曼树#####*/

// 哈夫曼字符表的最大字符数量
#define MAX_ZI_FU_NUM 128
// 哈夫曼编码表的最大编码长度
#define MAX_BIAN_MA_LEN 64

// 哈夫曼树结点
typedef struct HaFuManShuJieDian {
    // 结点类型：0=临时结点；1=字符结点
    int iLeiXing;
    // 结点权重
    int iQuanZhong;
    // 字符
    char cZiFu;
    // 左结点指针
    struct HaFuManShuJieDian *pHFMSJDZuo;
    // 右结点指针
    struct HaFuManShuJieDian *pHFMSJDYou;
} HFMSJD;

// 哈夫曼字符表和哈夫曼编码表，两者下标对应
char carrHafuManZiFu[MAX_ZI_FU_NUM] = {'\0'};
char carr2HafuManBianMa[MAX_ZI_FU_NUM][MAX_BIAN_MA_LEN] = {'\0'};

// 构造哈夫曼树
extern void gouZaoHaFuManShu(HFMSJD **, char *, int *);
// 构造哈夫曼编码表
extern void gouZaoHaFuManBianMaBiao(HFMSJD *, int *, char *, int);

/*#####实现代码#####*/

int main() {
    // 待处理字符串
    char sDaiChuLi[] = "hello world";
    // 字符数组和字符权重数组，两者下标对应
    char carrZiFu[MAX_ZI_FU_NUM] = {'\0'};
    int iarrZiFuQuanZhong[MAX_ZI_FU_NUM] = {0};
    // 临时字符权重数组，用于统计字符权重
    int tiarrZiFuQuanZhong[MAX_ZI_FU_NUM] = {0};
    // 哈夫曼树根节点
    HFMSJD *pHFMSJDTou = NULL;
    // 哈夫曼字符表数量
    int iHafuManZiFuNum = 0;
    // 临时字符串，用于构造哈夫曼编码
    char tsBianMa[64] = "";

    // 统计字符权重
    for (int i = 0; sDaiChuLi[i] != '\0'; i++) {
        // 将字符转换成ASCII码值
        tiarrZiFuQuanZhong[(int)sDaiChuLi[i]]++;
    }
    for (int i = 0, j = 0; i < MAX_ZI_FU_NUM; i++) {
        if (tiarrZiFuQuanZhong[i] != 0) {
            carrZiFu[j] = (char)i;
            iarrZiFuQuanZhong[j] = tiarrZiFuQuanZhong[i];
            j++;
        }
    }

    gouZaoHaFuManShu(&pHFMSJDTou, carrZiFu, iarrZiFuQuanZhong);
    gouZaoHaFuManBianMaBiao(pHFMSJDTou, &iHafuManZiFuNum, &tsBianMa, 0);

    for (int i = 0; i < iHafuManZiFuNum; i++) {
        printf("%c:", carrHafuManZiFu[i]);
        for (int j = 0; carr2HafuManBianMa[i][j] != '\0'; j++) {
            printf("%c", carr2HafuManBianMa[i][j]);
        }
        printf("\n");
    }

    return 0;
}

void gouZaoHaFuManShu(HFMSJD **ppHFMSJDTou, char *carrZiFu, int *iarrZiFuQuanZhong) {
    // 保存所有的字符结点的指针数组
    HFMSJD *tparrHFMSJD[MAX_ZI_FU_NUM] = {NULL};
    // 临时结点指针
    HFMSJD *tpHFMSJD1 = NULL, *tpHFMSJD2 = NULL, *tpHFMSJD3 = NULL;
    // 临时结点指针在指针数组中的下标
    int tiJieDianXiaBiao1 = -1, tiJieDianXiaBiao2 = -1;
    // 创建所有的字符结点
    for (int i = 0, j = 0; i < MAX_ZI_FU_NUM; i++) {
        if (carrZiFu[i] != '\0') {
            tparrHFMSJD[j] = (HFMSJD *)malloc(sizeof(HFMSJD));
            tparrHFMSJD[j]->iLeiXing = 1;
            tparrHFMSJD[j]->iQuanZhong = iarrZiFuQuanZhong[i];
            tparrHFMSJD[j]->cZiFu = carrZiFu[i];
            tparrHFMSJD[j]->pHFMSJDZuo = NULL;
            tparrHFMSJD[j]->pHFMSJDYou = NULL;
            j++;
        }
    }
    while (1) {
        tpHFMSJD1 = NULL;
        tpHFMSJD2 = NULL;
        // 查找指针数组中结点权重最小的两个结点
        for (int i = 0; i < MAX_ZI_FU_NUM; i++) {
            if (tparrHFMSJD[i] == NULL) {
                continue;
            }
            if (tpHFMSJD1 == NULL) {
                tiJieDianXiaBiao1 = i;
                tpHFMSJD1 = tparrHFMSJD[i];
            } else if (tpHFMSJD2 == NULL) {
                tiJieDianXiaBiao2 = i;
                tpHFMSJD2 = tparrHFMSJD[i];
            } else {
                if (tparrHFMSJD[i]->iQuanZhong < tpHFMSJD1->iQuanZhong) {
                    tiJieDianXiaBiao1 = i;
                    tpHFMSJD1 = tparrHFMSJD[i];
                } else if (tparrHFMSJD[i]->iQuanZhong < tpHFMSJD2->iQuanZhong) {
                    tiJieDianXiaBiao2 = i;
                    tpHFMSJD2 = tparrHFMSJD[i];
                }
            }
        }
        if (tpHFMSJD1 != NULL && tpHFMSJD2 != NULL) {
            // 如果能找到两个结点，就以这两个结点作为子结点构造一个父结点
            tpHFMSJD3 = (HFMSJD *)malloc(sizeof(HFMSJD));
            tpHFMSJD3->iLeiXing = 0;
            tpHFMSJD3->iQuanZhong = tpHFMSJD1->iQuanZhong + tpHFMSJD2->iQuanZhong;
            tpHFMSJD3->cZiFu = '\0';
            tpHFMSJD3->pHFMSJDZuo = tpHFMSJD1;
            tpHFMSJD3->pHFMSJDYou = tpHFMSJD2;
            // 把原来的两个结点指针数组中移除，把新构造的结点放入指针数组
            tparrHFMSJD[tiJieDianXiaBiao1] = tpHFMSJD3;
            tparrHFMSJD[tiJieDianXiaBiao2] = NULL;
        } else {
            // 指针数组中只剩一个结点，那么哈夫曼树就已经构造完成了
            if (tpHFMSJD1 != NULL) {
                *ppHFMSJDTou = tpHFMSJD1;
                break;
            } else {
                *ppHFMSJDTou = tpHFMSJD2;
                break;
            }
        }
    }
}

void gouZaoHaFuManBianMaBiao(HFMSJD *tpHFMSJD, int *piHafuManZiFuNum, char *sBianMa, int iBianMalen) {
    // 构造临时编码数组，拷贝上次递归传递进来的编码数组
    char tsBianMa[64] = {'\0'};
    int iLen1 = 0, iLen2 = 0;

    for (int i = 0; sBianMa[i] != '\0'; i++) {
        tsBianMa[i] = sBianMa[i];
    }
    if (tpHFMSJD->iLeiXing == 0) {
        // 如果是临时结点就继续递归
        if (tpHFMSJD->pHFMSJDZuo != NULL) {
            iLen1 = iBianMalen;
            tsBianMa[iLen1] = '0';
            iLen1++;
            gouZaoHaFuManBianMaBiao(tpHFMSJD->pHFMSJDZuo, piHafuManZiFuNum, tsBianMa, iLen1);
        }
        if (tpHFMSJD->pHFMSJDYou != NULL) {
            iLen2 = iBianMalen;
            tsBianMa[iLen2] = '1';
            iLen2++;
            gouZaoHaFuManBianMaBiao(tpHFMSJD->pHFMSJDYou, piHafuManZiFuNum, tsBianMa, iLen2);
        }
    } else {
        // 如果是字符结点，那么该字符就完成了编码
        carrHafuManZiFu[*piHafuManZiFuNum] = tpHFMSJD->cZiFu;
        for (int i = 0; i < iBianMalen; i++) {
            carr2HafuManBianMa[*piHafuManZiFuNum][i] = tsBianMa[i];
        }
        *piHafuManZiFuNum = (*piHafuManZiFuNum) + 1;
    }
}