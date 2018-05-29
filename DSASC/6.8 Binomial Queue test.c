#include<stdio.h>
#include<time.h>
#include"../Library/s_and_r.h"
#include"../Library/General.h"
#include"6.8 Binomial Queue.h"

#define MAXLENGTH 15

void PrintElement(ElementType X);

int main(void)
{
	BinQueue BQ1, BQ2;
	int list1[MAXLENGTH], list2[MAXLENGTH];
	//int random;

	BQ1 = Initialize();
	BQ2 = Initialize();
	// Generate two random arrays
	printf("List 1:\n");
	for (int i = 0; i < MAXLENGTH; i++)
	{
		list1[i] = Random(MinData, MaxData);
		printf("%d ", list1[i]);
	}
	puts("");
	printf("List 2:\n");
	for (int i = 0; i < MAXLENGTH; i++)
	{
		list2[i] = Random(MinData, MaxData);
		printf("%d ", list2[i]);
	}
	puts("");
	puts("\n");
	// Insert elements of array to BinQueue
	printf("BinQueue1:\n");
	for (int i = 0; i < MAXLENGTH; i++)
	{
		printf("------------\n");
		Insert(list1[MAXLENGTH - i - 1], BQ1);
		printf("After Insert %4d(%d): ", list1[MAXLENGTH - i - 1], i + 1);
		Traverse(BQ1, PrintElement);
		puts("");
	}
	puts("\n");
	printf("BinQueue2:\n");
	for (int i = 0; i < MAXLENGTH; i++)
	{
		printf("------------\n");
		Insert(list2[MAXLENGTH - i - 1], BQ2);
		printf("After Insert %4d(%d): ", list2[MAXLENGTH - i - 1], i + 1);
		Traverse(BQ2, PrintElement);
		puts("");
	}
	puts("\n");
	puts("\n\n");

	// Merge
	BQ1 = Merge(BQ1, BQ2);
	printf("************\n");
	printf("After Merge:\n");
	Traverse(BQ1, PrintElement);
	printf("\n************\n");
	puts("\n\n");

	// Delete elements
	for (int i = 0; i < MAXLENGTH*2; i++)
	{
		printf("------------\n");
		printf("After Delete %4d: ", FindMin(BQ1));
		DeleteMin(BQ1);
		Traverse(BQ1, PrintElement);
		puts("");
	}
	//for (int i = 0; i < MAXLENGTH; i++)
	//{
	//	printf("------------\n");
	//	printf("After Delete %4d: ", FindMin(BQ2));
	//	DeleteMin(BQ2);
	//	Traverse(BQ2, PrintElement);
	//	puts("");
	//}

	BQ1 = MakeEmpty(BQ1);
	BQ2 = MakeEmpty(BQ2);
	return 0;
}

void PrintElement(ElementType X)
{
	if (X >= MinData && X < MaxData)
		printf("%5d", X);
}