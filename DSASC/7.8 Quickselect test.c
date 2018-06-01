/*	Compiles with
	7.2 Insertion Sort.h
	7.2 Insertion Sort.c
	7.8 Quickselect.h
	7.8 Quickselect.c
	../Library/s_and_r.h
	../Library/s_and_r.c
	../Library/General.h
	../Library/General.c
*/

#include<stdio.h>
#include"../Library/s_and_r.h"
#include"7.8 Quickselect.h"

#define MAXLENGTH 20
#define MinData 0
#define MaxData 10000

void PrintList(ElementType List[], int Length);

int main(void)
{
	int list[MAXLENGTH];
	int k = 1;
	ElementType Found;

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

	// Quickselect
	printf("Quickselect:\n");
	for (int i = 0; i < MAXLENGTH; i++)
	{
		Found = Quickselect(list, MAXLENGTH, i + 1);
		printf("%4d ", Found);
	}
	puts("");

	// Quicksort (For comparison)
	printf("After quicksort:\n");
	Quicksort(list, MAXLENGTH);
	PrintList(list, MAXLENGTH);
	return 0;
}

void PrintList(ElementType List[], int Length)
{
	for (int i = 0; i < Length; i++)
		printf("%4d ", List[i]);
	puts("");
}
