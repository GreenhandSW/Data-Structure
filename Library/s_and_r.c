/* s_and_r.c -- 包含函数rand1()和srand1()的文件 */
/* 使用ANSI C 的可移植算法 */
#include<time.h>
#include "s_and_r.h"

static unsigned long int next = 1;			// 种子
int rand1(void)
{
/* 产生伪随机数的魔法般的公式 */
	next = next * 1103515245 + 12345;
	return (unsigned int)(next / 65536) % 32768;
}

void srand1(unsigned int seed)
{
	next = seed;
}


int Random(int min, int max)
{
	srand1((unsigned)time(0)*rand1());

	return rand1() % (max - min) + min;
}

void GenerateRandomString(char * random_str, int L)
{
	int i;
	srand1((unsigned)time(0)*rand1());
	for (i = 0; i < L-1; i++)
	{
		random_str[i] = Random(0, 26) + 'a';
	}
	random_str[i] = '\0';
}
