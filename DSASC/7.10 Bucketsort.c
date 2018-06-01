/*	Compiles with
	../Library/s_and_r.h
	../Library/s_and_r.c
*/

#include<stdio.h>
#include"../Library/s_and_r.h"

#define MAXLENGTH 30
#define MinData 0
#define MaxData 100

void PrintList(unsigned List[], int Length);
// just for data set with a very small max number,
// or it's space cost would be too expensive.
void Bucketsort(unsigned List[], int Length);

int main(void)
{
	unsigned list[MAXLENGTH];

	// Generate a random array
	for (int i = 0; i < MAXLENGTH; i++)
		list[i] = (unsigned)Random(MinData, MaxData);

	// Index
	for (int i = 0; i < MAXLENGTH; i++)
		printf("%3d ", i);
	puts("");
	// Initial List
	printf("Initial List:\n");
	PrintList(list, MAXLENGTH);

	// Bucketsort
	printf("After Bucketsort:\n");
	Bucketsort(list, MAXLENGTH);
	PrintList(list, MAXLENGTH);
	return 0;
}

void PrintList(unsigned List[], int Length)
{
	for (int i = 0; i < Length; i++)
		printf("%3u ", List[i]);
	puts("");
}

void Bucketsort(unsigned List[], int Length)
{
	unsigned Count[MaxData];

	for (int i = 0; i < MaxData; i++)
		Count[i] = 0;
	for (int i = 0; i < Length; i++)
		Count[List[i]]++;
	for (int i = 0, j = 0; i < MaxData; i++)
		while (Count[i] > 0)
		{
			List[j++] = i;
			Count[i]--;
		}
}
