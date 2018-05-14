#include<stdio.h>
#include"练习3.1 list.h"
#include"D:\Programming\CPP\程序清单12.9 s_and_r.c 程序.c"
#include<time.h>
#define MAX 100

void PrintItem(Item item)
{
	printf("%5d ", item);
}

int main(void)
{
	List L;

	InitializeList(&L);

	srand1((unsigned)time(0));
	for (int i = 0; i < MAX; i++)
		AddItem(rand1(), &L);
	Traverse(&L, PrintItem);

	return 0;
}

