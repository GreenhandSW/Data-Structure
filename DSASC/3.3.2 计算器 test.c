#include<stdio.h>
//#include"3.3.2 ջ������ʵ�� Stack.h"
#include"3.3.2 ������.h"

#define MAX 100
int
main(void)
{
	char src[MAX] = "2^8-1+3^2^4";
	char dst[MAX * 2];

	Infix2Postfix(src, dst);
	puts("");
	puts(dst);
	double outcome = Calc(dst);
	printf("%s = %0.2lf\n", src, outcome);

	return 0;
}