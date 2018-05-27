#include<stdio.h>
#include<stdlib.h>
#include"../Library/General.h"
#include"6.3 Binary Heap.h"

#define MinPQSize 10

struct HeapStruct
{
	int Capacity;
	int Size;
	ElementType * Elements;
};

int Compare(ElementType a, ElementType b)
{
	if (a < b)
		return SMALLER;
	else if (a == b)
		return EQUAL;
	else
		return BIGGER;
}

PriorityQueue Initialize(int MaxElements)
{
	PriorityQueue Q;

	if (MaxElements < MinPQSize)
	{
		Error("Priority queue size is too small!\n");
		exit(1);
	}

	Q = malloc(sizeof(HeapStruct));
	if (!Q)
		FatalError("Out of space!!!\n");

	// Allocate the array plus one extra for sentinel
	Q->Elements = malloc((MaxElements + 1) * sizeof(ElementType));
	if (!(Q->Elements))
		FatalError("Out of space!!!\n");

	Q->Capacity = MaxElements;
	Q->Size = 0;
	Q->Elements[0] = MinData;

	return Q;
}

void Destroy(PriorityQueue Q)
{
	free(Q->Elements);
	Q->Elements = NULL;
}

PriorityQueue MakeEmpty(PriorityQueue Q)
{
	Destroy(Q);
	free(Q);

	return NULL;
}

void Insert(ElementType X, PriorityQueue Q)
{
	int i;
	if (IsFull(Q))
		Error("Priority queue is full!\n");
	else
	{
		for (i = ++(Q->Size); Q->Elements[i / 2] > X; i /= 2)
			Q->Elements[i] = Q->Elements[i / 2];
		Q->Elements[i] = X;
	}
}

ElementType DeleteMin(PriorityQueue Q)
{
	int i, Child;
	ElementType MinElement, LastElement;

	if (IsEmpty(Q))
	{
		Error("Priority queue is empty!\n");
		return Q->Elements[0];
	}
	MinElement = Q->Elements[1];
	LastElement = Q->Elements[(Q->Size)--];

	for (i = 1; i * 2 <= Q->Size; i = Child)
	{
		// Find smaller child
		Child = i * 2;
		if (Child != Q->Size &&
			Compare(Q->Elements[Child + 1], Q->Elements[Child]) == SMALLER)
			Child++;
		// Precolate one level
		if (Compare(LastElement, Q->Elements[Child]) == BIGGER)
			Q->Elements[i] = Q->Elements[Child];
		else
			break;
	}
	Q->Elements[i] = LastElement;

	return MinElement;
}

ElementType FindMin(PriorityQueue Q)
{
	if (Q->Size >= 1)
		return Q->Elements[1];
	else
		return Q->Elements[0];
}

bool IsFull(PriorityQueue Q)
{
	if (Q->Size == Q->Capacity)
		return true;
	else
		return false;
}

bool IsEmpty(PriorityQueue Q)
{
	if (Q->Size == 0)
		return true;
	else
		return false;
}

void Traverse(PriorityQueue Q, void(*pfun)(ElementType X))
{
	for (int i = 1; i <= Q->Size; i++)
		pfun(Q->Elements[i]);
}
