#include<stdio.h>
#include<time.h>
#include"../Library/s_and_r.h"
#include"../Library/General.h"
#include"4.4 AvlTree.h"

#define MAXLENGTH 20

void PrintElement(ElementType X);

int main(void)
{
	AvlTree T;
	int list[MAXLENGTH];
	int random;
	int count = MAXLENGTH - 1;

	T = MakeEmpty(NULL);
	for (int i = 0; i < MAXLENGTH; i++)
	{
		srand1((unsigned)time(0)*(i + 1));
		list[i] = Random(0, 100);
		printf("%d ", list[i]);
	}
	puts("");
	for (int i = 0; i < MAXLENGTH; i++)
	{
		T = Insert(list[i], T);
		printf("After Insert %2d: ", list[i]);
		InOrder(T, PrintElement);
		puts("");
	}
	while (T)
	{
		random = Random(0, count + 1);
		T = Delete(list[random], T);
		int deleted = list[random];

		Swap(&(list[random]), &(list[count]));
		count--;
		printf("After Delete %2d: ", deleted);
		InOrder(T, PrintElement);
		puts("");
	}

	T = MakeEmpty(T);
	return 0;
}

void PrintElement(ElementType X)
{
	printf("%2d ", X);
}