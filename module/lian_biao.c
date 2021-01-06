#include <stdio.h>
#include <stdlib.h>
#include "../include/lian_biao.h"

void chuShiHua()
{
    head = NULL;
    tail = NULL;
}

void TianJiaXiang(int num)
{
    struct JieDian *temp = (struct JieDian *)malloc(sizeof(struct JieDian));
    temp->num = num;
    temp->next = NULL;
    if (head == NULL)
    {
        head = temp;
        tail = temp;
    }
    else
    {
        tail->next = temp;
        tail = temp;
    }
}

void ShuChuLianBiao()
{
    if (head == NULL)
    {
        printf("kong1lian4biao3!\n");
        return;
    }
    struct JieDian *p = head;
    while (p != NULL)
    {
        printf("%d ", p->num);
        p = p->next;
    }
    printf("\n");
}