#include <stdio.h>
#include <stdlib.h>
#include "SeqList.h"
int main()
{
    SeqList L;
    SLInit(&L);
    SLPushBack(&L,1);
    SLPushBack(&L,5);
    SLPushBack(&L,9);
    SLPushBack(&L,7);
    SLPrit(L);
    exit(0);
}
