#include<stdio.h>
#include<time.h>
#include"../Library/s_and_r.h"
#include"../Library/General.h"
#include"6.6 Leftist Heap.h"

#define MAXLENGTH 15

void PrintElement(ElementType X);

int main(void)
{
	PriorityQueue Q;
	int list[MAXLENGTH];
	//int random;

	Q = Initialize();
	// Generate a random array
	for (int i = 0; i < MAXLENGTH; i++)
	{
		list[i] = Random(MinData, MaxData);
		printf("%d ", list[i]);
	}
	puts("");

	// Insert elements of array to PriorityQueue
	for (int i = 0; i < MAXLENGTH; i++)
	{
		printf("------------\n");
		Insert(list[MAXLENGTH - i - 1], Q);
		printf("After Insert %4d: ", list[MAXLENGTH - i - 1]);
		Traverse(Q, PrintElement);
		puts("");
	}
	puts("\n");

	// Delete elements
	for (int i = 0; i < MAXLENGTH; i++)
	{
		printf("------------\n");
		printf("After Delete %4d: ", FindMin(Q));
		Q = DeleteMin1(Q);
		Traverse(Q, PrintElement);
		puts("");
	}

	Q = MakeEmpty(Q);
	return 0;
}

void PrintElement(ElementType X)
{
	if (X >= MinData && X < MaxData)
		printf("%5d", X);
}