#include <stdio.h>

#include "tool1.h"

void mytool1()
{
    printf("[%s,%d]\n", __FUNCTION__, __LINE__);
}
