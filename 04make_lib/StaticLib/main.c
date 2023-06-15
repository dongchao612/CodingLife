#include <stdio.h> // 头文件展开

void f1();
void f2();

int main(int argc, char const *argv[])
{
    printf("[%s,%d]\n", __FUNCTION__, __LINE__);
    f1();
    f2();

    return 0;
}