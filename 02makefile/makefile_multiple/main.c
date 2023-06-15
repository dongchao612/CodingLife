#include <stdio.h>
#include <stdlib.h>

#include "tool1.h"
#include "tool2.h"

int main()
{
    printf("[%s,%d]\n", __FUNCTION__, __LINE__);
    mytool1();
    mytool2();

    exit(0);
}