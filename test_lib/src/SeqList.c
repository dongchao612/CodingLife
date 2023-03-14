#include "SeqList.h"
#include <stdio.h>
#include <stdlib.h>
void SLInit(SeqList *L) 
{
    L->size = 0;
}

void SLPushBack(SeqList *L, SLDataType x)
{
    L->data[L->size] = x;
    L->size++;
}

void SLPrit(const SeqList L)
{
    for (size_t i = 0; i < L.size; i++)
    {
        printf("%d\t", L.data[i]);
    }
    printf("\n");
}
