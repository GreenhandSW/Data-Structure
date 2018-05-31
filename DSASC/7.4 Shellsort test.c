#include<stdio.h>
#include"../Library/s_and_r.h"
#include"7.4 Shellsort.h"

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

	//// Shellsort with Shell increment sequence
	//Shellsort(list, MAXLENGTH);
	//printf("After Shellsort:\n");
	//PrintList(list, MAXLENGTH);

	//// Shellsort with Hibbard increment sequence
	//ShellsortHibbard(list, MAXLENGTH);
	//printf("After Shellsort with Hibbard increment:\n");
	//PrintList(list, MAXLENGTH);

	// Shellsort with Sedgewick increment sequence
	ShellsortSedegwick(list, MAXLENGTH);
	printf("After Shellsort with Sedgewick increment:\n");
	PrintList(list, MAXLENGTH);

	return 0;
}

void PrintList(ElementType List[], int Length)
{
	for (int i = 0; i < Length; i++)
		printf("%4d ", List[i]);
	puts("");
}
