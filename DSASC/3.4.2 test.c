#include<stdio.h>
#include"../../../CPP/程序清单12.9 s_and_r.c 程序.c"
#include"3.4.2 队列的循环实现 Queue.h"
#include<Windows.h>
#include<time.h>

#define TEST_SIZE 100

int
Probability(void)
{
	return rand1() >= 32768/2;
}

int main(void)
{
	Queue Q = CreateQueue(20);
	int x;
	int count = 0;

	srand1((unsigned)time(0));
	for (int i = 0; i < TEST_SIZE; i++)
	{
		x = Probability();
		if (x == 1)
		{
			count++;
			EnQueue(rand1(), Q);
		}
		else
			if(!IsEmpty(Q))
				DeQueue(Q);
		PrintQueue(Q);
		Sleep(500);
	}
	printf("\n%d\n",count);
	DisposeQueue(Q);

	return 0;
}