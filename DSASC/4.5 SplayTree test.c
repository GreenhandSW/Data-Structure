#include<stdio.h>
#include<time.h>
#include"../Library/s_and_r.h"
#include"../Library/General.h"
#include"4.5 SplayTree.h"

#define MAXLENGTH 20

void PrintElement(ElementType X);

int main(void)
{
	AvlTree T;
	int list[MAXLENGTH];
	//int random;
	int count = MAXLENGTH - 1;

	T = MakeEmpty(NULL);
	for (int i = 0; i < MAXLENGTH; i++)
	{
		//srand1((unsigned)time(0)*(i + 1));
		list[i] = i * 2;
		printf("%d ", list[i]);
	}
	puts("");
	for (int i = 0; i < MAXLENGTH; i++)
	{
		T = Insert(list[MAXLENGTH - i - 1], T);
		printf("After Insert %2d: ", list[i]);
		InOrder(T, PrintElement);
		puts("");
	}

	int i = 0;
	while (T)
	{
		
		T = Find(list[i], T);

		int found = list[i];
		printf("After Finding %2d: ", found);
		InOrder(T, PrintElement);
		puts("");
		i++;
	}

	T = MakeEmpty(T);
	return 0;
}

void PrintElement(ElementType X)
{
	printf("%2d ", X);
}