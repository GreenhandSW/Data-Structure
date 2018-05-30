#include<stdio.h>
#include<time.h>
#include"../Library/s_and_r.h"
#include"../Library/General.h"
#include"Practice 6.5.h"

#define MAXLENGTH 15

int main(void)
{
	PriorityQueue Q;
	int list[MAXLENGTH];
	//int random;
	int count = MAXLENGTH - 1;

	// Generate a random array and initialize the PriorityQueue with it
	for (int i = 0; i < MAXLENGTH; i++)
	{
		list[i] = Random(MinData, MaxData);
		printf("%d ", list[i]);
	}
	puts("");
	Q = Initialize(list, MAXLENGTH);
	printf("Before Build:\n");
	Traverse(Q, PrintElement);
	puts("");
	// build the initial array into Heap
	BuildHeap(Q);
	// The Initial Heap
	printf("The Initial Heap:\n");
	Traverse(Q, PrintElement);
	puts("");
	// Increase a Key
	IncreaseKey(5, 4000, Q);
	printf("After Increase:\n");
	Traverse(Q, PrintElement);
	puts("");

	// Decrease a Key
	DecreaseKey(15, GetValue(15, Q), Q);
	printf("After Decrease:\n");
	Traverse(Q, PrintElement);
	puts("");

	// Delete an element
	Delete(3, Q);
	printf("After Delete:\n");
	Traverse(Q, PrintElement);
	puts("");

	Q = MakeEmpty(Q);
	return 0;
}