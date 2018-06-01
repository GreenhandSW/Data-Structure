/*	Compiles with
	7.2 Insertion Sort.h
	7.2 Insertion Sort.c
	7.7 Quicksort.c
	../Library/s_and_r.h
	../Library/s_and_r.c
	../Library/General.h
	../Library/General.c
*/

#include<stdio.h>
#include"../Library/s_and_r.h"
#include"7.7 Quicksort.h"

#define MAXLENGTH 20
#define MinData 0
#define MaxData 10000

void PrintList(ElementType List[], int Length);

int main(void)
{
	int list[MAXLENGTH];

	// Generate a random array
	for (int i = 0; i < MAXLENGTH; i++)
		list[i] = Random(MinData, MaxData);

	// Index
	for (int i = 0; i < MAXLENGTH; i++)
		printf("%4d ", i);
	puts("");
	// Initial List
	printf("Initial List:\n");
	PrintList(list, MAXLENGTH);

	// Quicksort
	Quicksort(list, MAXLENGTH);
	printf("After Quicksort:\n");
	PrintList(list, MAXLENGTH);

	return 0;
}

void PrintList(ElementType List[], int Length)
{
	for (int i = 0; i < Length; i++)
		printf("%4d ", List[i]);
	puts("");
}
