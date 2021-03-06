#include<stdio.h>
#include"../Library/s_and_r.h"
#include"7.2 Insertion Sort.h"

#define MAXLENGTH 40
#define MinData 0
#define MaxData 10000

void PrintList(ElementType List[], int Length);

int main(void)
{
	int list[MAXLENGTH];

	// Generate a random array
	for (int i = 0; i < MAXLENGTH; i++)
		list[i] = Random(MinData, MaxData);
	printf("Initial List:\n");
	PrintList(list, MAXLENGTH);

	// Insertion Sort
	InsertionSort(list, MAXLENGTH);
	printf("After Insertion Sort:\n");
	PrintList(list, MAXLENGTH);

	return 0;
}

void PrintList(ElementType List[], int Length)
{
	for (int i = 0; i < Length; i++)
		printf("%4d ", List[i]);
	puts("");
}
