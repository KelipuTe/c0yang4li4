#ifndef _LIAN_BIAO_H
#define _LIAN_BIAO_H

struct JieDian
{
    int num;
    struct JieDian *next;
};

struct JieDian *head;
struct JieDian *tail;

extern void chuShiHua();
extern void TianJiaXiang(int num);
extern void ShuChuLianBiao();

#endif