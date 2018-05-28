#include<stdio.h>
#include<stdlib.h>
#include"../Library/General.h"
#include"6.6 Leftist Heap.h"

#define MinPQSize 10

struct TreeNode
{
	ElementType Element;
	PriorityQueue Left;
	PriorityQueue Right;
	int Npl;
};

static int Compare(ElementType a, ElementType b);
static void SwapChildren(PriorityQueue Q);
static PriorityQueue Merge1(PriorityQueue Q1, PriorityQueue Q2);

static void SwapChildren(PriorityQueue Q)
{
	PriorityQueue tmp;

	tmp = Q->Left;
	Q->Left = Q->Right;
	Q->Right = tmp;
}

static PriorityQueue Merge1(PriorityQueue Q1, PriorityQueue Q2)
{
	if (Q1->Left == NULL)	// Single node
		Q1->Left = Q2;		// Q1->Right is already NULL,
							// Q1->Npl is already 0
	else
	{
		Q1->Right = Merge(Q1->Right, Q2);
		if (Q1->Left->Npl < Q1->Right->Npl)
			SwapChildren(Q1);
		Q1->Npl = Q1->Right->Npl + 1;
	}

	return Q1;
}
static int Compare(ElementType a, ElementType b)
{
	if (a < b)
		return SMALLER;
	else if (a == b)
		return EQUAL;
	else
		return BIGGER;
}

PriorityQueue Initialize(void)
{
	return NULL;
}

PriorityQueue MakeEmpty(PriorityQueue Q)
{
	if (Q)
	{
		MakeEmpty(Q->Left);
		MakeEmpty(Q->Right);
		free(Q);
	}

	return NULL;
}

PriorityQueue Insert1(ElementType X, PriorityQueue Q)
{
	PriorityQueue SingleNode;

	SingleNode = malloc(sizeof(TreeNode));
	if (!SingleNode)
		FatalError("Out of space!!!\n");
	else
	{
		SingleNode->Element = X;
		SingleNode->Npl = 0;
		SingleNode->Left = NULL;
		SingleNode->Right = NULL;
		Q = Merge(SingleNode, Q);
	}

	return Q;
}

PriorityQueue DeleteMin1(PriorityQueue Q)
{
	PriorityQueue LeftHeap, RightHeap;

	if (IsEmpty(Q))
	{
		Error("Priority queue is empty!\n");
		return Q;
	}
	else
	{
		LeftHeap = Q->Left;
		RightHeap = Q->Right;
		free(Q);
		return Merge(LeftHeap, RightHeap);
	}
}

ElementType FindMin(PriorityQueue Q)
{
	if (Q)
		return Q->Element;
	else
		return MinData - 1;	// means data error
}

bool IsEmpty(PriorityQueue Q)
{
	if (!Q)
		return true;
	else
		return false;
}

PriorityQueue Merge(PriorityQueue Q1, PriorityQueue Q2)
{
	if (Q1 == NULL)
		return Q2;
	else if (Q2 == NULL)
		return Q1;
	else if (Compare(Q1->Element, Q2->Element) == SMALLER)
		return Merge1(Q1, Q2);
	else
		return Merge1(Q2, Q1);
}

void Traverse(PriorityQueue Q, void(*pfun)(ElementType X))
{
	if (Q)
	{
		Traverse(Q->Left, pfun);
		pfun(Q->Element);
		Traverse(Q->Right, pfun);
	}
}
