#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"../Library/General.h"
#include"Practice 6.5.h"

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
void subFindSmaller(ElementType X, PriorityQueue Q, Position P, void(*pfun)(ElementType X));

PriorityQueue Initialize(ElementType list[], int Length)
{
	PriorityQueue Q;

	Q = malloc(sizeof(HeapStruct));
	if (!Q)
		FatalError("Out of space!!!\n");

	// Allocate the array plus one extra for sentinel
	Q->Elements = malloc((Length + 1) * sizeof(ElementType));
	if (!(Q->Elements))
		FatalError("Out of space!!!\n");

	Q->Elements[0] = -Infinity;
	memcpy(Q->Elements + 1, list, Length * sizeof(ElementType));
	Q->Capacity = Length;
	Q->Size = Length;

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
	{
		if ((1 << Log2Ceiling(i)) == i)
			puts("");
		pfun(Q->Elements[i]);
	}
	printf("\n-------------------------------");
}

void PercolateUp(PriorityQueue Q, Position P)
{
	Position i;
	ElementType Record = Q->Elements[P];

	for (i = P; Compare(Q->Elements[i / 2], Record) == BIGGER; i /= 2)
		Q->Elements[i] = Q->Elements[i / 2];
	Q->Elements[i] = Record;
}

void PercolateDown(PriorityQueue Q, Position P)
{
	Position i, Child;
	ElementType Record = Q->Elements[P];

	for (i = P; i * 2 <= Q->Size; i = Child)
	{
		// Find smaller child
		Child = i * 2;
		if (Child != Q->Size &&
			Compare(Q->Elements[Child + 1], Q->Elements[Child]) == SMALLER)
			Child++;
		// Percolate down one level
		// I was stuck in here for a long time, and then I found that I can't
		// compare the elements in position P and Child, because the element 
		// in position P is already changed. So I have to compare the initial
		// element in Position P(that is Record) with the element in Position
		// Child.
		if (Compare(Record, Q->Elements[Child]) == BIGGER)
			Q->Elements[i] = Q->Elements[Child];
		else
			break;
	}
	Q->Elements[i] = Record;
}

void DecreaseKey(Position P, ElementType Delta, PriorityQueue Q)
{
	if ((0 <= P) && (P <= Q->Size))
	{
		Q->Elements[P] -= Delta;
		PercolateUp(Q, P);
	}
}

void IncreaseKey(Position P, ElementType Delta, PriorityQueue Q)
{
	if ((1 <= P) && (P <= Q->Size))
	{
		Q->Elements[P] += Delta;
		PercolateDown(Q, P);
	}
}

ElementType Delete(Position P, PriorityQueue Q)
{
	ElementType Data;

	Data = Q->Elements[P];
	DecreaseKey(P, Infinity, Q);
	DeleteMin(Q);

	return Data;
}

void BuildHeap(PriorityQueue Q)
{
	for (int i = Q->Size / 2; i > 0; i--)
		PercolateDown(Q, i);
}

int GetCurSize(PriorityQueue Q)
{
	return Q->Size;
}

ElementType GetValue(Position P, PriorityQueue Q)
{
	if (P > 0 && P <= Q->Size)
		return Q->Elements[P];
	else
		return Q->Elements[0];
}

void FindSmaller(ElementType X, PriorityQueue Q, void(*pfun)(ElementType X))
{
	subFindSmaller(X, Q, 1, pfun);
}

void PrintElement(ElementType X)
{
	//if (X >= MinData && X < MaxData)
		printf("%5d", X);
}

void subFindSmaller(ElementType X, PriorityQueue Q, Position P, void(*pfun)(ElementType X))
{
	if (0 < P && P <= Q->Size)
	{
		if (Compare(Q->Elements[P], X) == SMALLER)
		{
			pfun(Q->Elements[P]);
			subFindSmaller(X, Q, P * 2, pfun);
			subFindSmaller(X, Q, P * 2 + 1, pfun);
		}
	}
}