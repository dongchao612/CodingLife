#ifndef __SEQLIST_H__
#define __SEQLIST_H__

#define N 10
typedef int SLDataType;
typedef struct SeqList
{
    SLDataType data[N];
    int size;
}SeqList;

void SLInit(SeqList* L);                    // 初始化
void SLPushBack(SeqList* L, SLDataType x);  //尾插
void SLPrit(SeqList ps);                    //打印


#endif