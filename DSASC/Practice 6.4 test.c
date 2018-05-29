#include<stdio.h>
#include<stdlib.h>
#include"../Library/s_and_r.h"
#include"../Library/General.h"

#define MAXLENGTH 15
#define MinData -100
#define MaxData 10000
#define Compare(X, Y) ((X>Y)?BIGGER:((X==Y)?EQUAL:SMALLER))
typedef int ElementType;
typedef ElementType * PriorityQueue;

void PercolateUp(PriorityQueue Q, int Length);
void PercolateDown(PriorityQueue Q, int Length);
void PrintPriorityQueue(PriorityQueue Q, int Length);

int main(void)
{
	PriorityQueue Q1, Q2;

	Q1 = malloc(sizeof(ElementType) * (MAXLENGTH + 1));
	Q2 = malloc(sizeof(ElementType) * (MAXLENGTH + 1));

	// Generate a random array
	Q1[0] = MinData;
	printf("Q 1:\n");
	for (int i = 1; i <= MAXLENGTH; i++)
	{
		Q1[i] = Random(MinData, MaxData);
	}
	// PrecolateUp Q1
	puts("Primary Q1:");
	PrintPriorityQueue(Q1, MAXLENGTH);
	PercolateUp(Q1, MAXLENGTH);
	puts("\n\nAfter Percolate up Q1:");
	PrintPriorityQueue(Q1, MAXLENGTH);
	puts("");


	// Generate a random array
	printf("\n\n\nQ 2:\n");
	Q2[0] = MinData;
	for (int i = 1; i <= MAXLENGTH; i++)
	{
		Q2[i] = Random(MinData, MaxData);
	}
	puts("Primary Q2:");
	PrintPriorityQueue(Q2, MAXLENGTH);
	// PrecolateUp Q2
	puts("\n\nAfter Percolate down Q2:");
	PercolateDown(Q2, MAXLENGTH);
	PrintPriorityQueue(Q2, MAXLENGTH);
	puts("");

	free(Q1);
	free(Q2);
	return 0;
}

void PercolateUp(PriorityQueue Q, int Length)
{
	for (int i = Length; i > 1; i /= 2)
	{
		for (int j = Length; j > 1; j--)
		{
			if (Compare(Q[j], Q[j / 2]) == SMALLER)
				Swap(&(Q[j]), &(Q[j / 2]));
		}
	}
}

void PercolateDown(PriorityQueue Q, int Length)
{
	int Child;
	for (int i = 1; i * 2 <= Length; i *= 2)
	{
		for (int j = 1; j * 2 <= Length; j++)
		{
			// Find smaller child
			Child = j * 2;
			// Child != Q->Size avoids Child+1 from overflow.
			if (Child != Length && Compare(Q[Child], Q[Child + 1]) == BIGGER)
				Child++;
			if (Compare(Q[j], Q[Child]) == BIGGER)
				Swap(&(Q[j]), &(Q[Child]));
		}
	}
}

void PrintPriorityQueue(PriorityQueue Q, int Length)
{
	printf("\n-----------------------------------");
	for (int i = 1; i <= Length; i++)
	{
		if ((1 << Log2Ceiling(i)) == i)
			puts("");
		printf("%4d ", Q[i]);
	}
}