#include <stdio.h>
#include <stdlib.h>

#define PRICE 10

#if 0
void f1()
{
    printf("hello world!\n");
}
#endif

int main()
{

	int i = 100;

	i = PRICE;
	
	printf("hello world\n");

	printf("i = %d\n",i);

	return 0;
}