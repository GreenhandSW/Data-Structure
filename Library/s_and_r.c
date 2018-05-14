/* s_and_r.c -- ��������rand1()��srand1()���ļ� */
/* ʹ��ANSI C �Ŀ���ֲ�㷨 */
#include<time.h>

static unsigned long int next = 1;			// ����
int rand1(void)
{
/* ����α�������ħ����Ĺ�ʽ */
	next = next * 1103515245 + 12345;
	return (unsigned int)(next / 65536) % 32768;
}

void srand1(unsigned int seed)
{
	next = seed;
}

int Random(int min, int max)
{
	srand1((unsigned)time(0));
	return rand1()%(max-min)+min;
}