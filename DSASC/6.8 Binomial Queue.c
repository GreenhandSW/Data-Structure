#include<stdio.h>
#include<stdlib.h>
#include"../Library/General.h"
#include"6.8 Binomial Queue.h"

#define MinPQSize 10
#define MaxTrees 8
#define Capacity ((2<<MaxTrees) - 1)
#define Infinity 2147483647

struct BinNode
{
	ElementType Element;
	Position LeftChild;
	Position NextSibling;
};

struct Collection
{
	int CurrentSize;
	BinTree TheTrees[MaxTrees];
};

static int Compare(ElementType a, ElementType b);
// Make a new tree with only one node and assign X to it.
static BinTree InsertIntoTree(ElementType X);
static void TraverseTree(BinTree T, void(*pfun)(ElementType X));

static int Compare(ElementType a, ElementType b)
{
	if (a < b)
		return SMALLER;
	else if (a == b)
		return EQUAL;
	else
		return BIGGER;
}

BinTree CombineTrees(BinTree T1, BinTree T2)
{
	if (Compare(T1->Element, T2->Element) == BIGGER)
		return CombineTrees(T2, T1);
	T2->NextSibling = T1->LeftChild;
	T1->LeftChild = T2;
	return T1;
}

// Merge two binomial queues
// Not optimized for early termination
// BQ1 contains merged result

BinQueue Initialize(void)
{
	BinQueue BQ;

	BQ = malloc(sizeof(Collection));
	if (!BQ)
		FatalError("Out of Space!!!\n");
	else
	{
		BQ->CurrentSize = 0;
		for (int i = 0; i < MaxTrees; i++)
			BQ->TheTrees[i] = NULL;
	}

	return BQ;
}

BinQueue Merge(BinQueue BQ1, BinQueue BQ2)
{
	BinTree T1, T2, Carry = NULL;

	if ((BQ1->CurrentSize + BQ2->CurrentSize) > Capacity)
	{
		Error("Merge would exceed capacity!\n");
		// avoid too many nests in the following sentences.
		return BQ1;
	}

	BQ1->CurrentSize += BQ2->CurrentSize;
	for (int i = 0, j = 1; j <= BQ1->CurrentSize; i++, j *= 2)
	{
		T1 = BQ1->TheTrees[i];
		T2 = BQ2->TheTrees[i];

		switch (!!T1+2*!!T2+4*!!Carry)
		{
		case 0: // No trees
		case 1: // Only BQ1
			break;
		case 2: // Only BQ2
			BQ1->TheTrees[i] = T2;
			BQ2->TheTrees[i] = NULL;
			break;
		case 4: // Only Carry
			BQ1->TheTrees[i] = Carry;
			Carry = NULL;
			break;
		case 3: // BQ1 and BQ2
			Carry = CombineTrees(T1, T2);
			BQ1->TheTrees[i] = NULL;
			BQ2->TheTrees[i] = NULL;
			break;
		case 5: // BQ1 and Carry
			Carry = CombineTrees(T1, Carry);
			BQ1->TheTrees[i] = NULL;
			break;
		case 6: // BQ2 and Carry
			Carry = CombineTrees(T2, Carry);
			BQ2->TheTrees[i] = NULL;
			break;
		case 7: // All three
			BQ1->TheTrees[i] = Carry;
			Carry = CombineTrees(T1, T2);
			BQ2->TheTrees[i] = NULL;
			break;
		}
	}

	return BQ1;
}

ElementType DeleteMin(BinQueue BQ)
{
	int MinTree;	// The tree with the minimum item
	BinQueue DeletedQueue;
	Position DeletedTree, OldRoot;
	ElementType MinItem;

	if (IsEmpty(BQ))
	{
		Error("Empty binomial queue!\n");
		return -Infinity;
	}

	MinItem = Infinity;
	for (int i = 0; i < MaxTrees; i++)
	{
		if (BQ->TheTrees[i] && Compare(BQ->TheTrees[i]->Element, MinItem) == SMALLER)
		{
			// Update minimum
			MinItem = BQ->TheTrees[i]->Element;
			MinTree = i;
		}
	}

	DeletedTree = BQ->TheTrees[MinTree];
	OldRoot = DeletedTree;
	DeletedTree = DeletedTree->LeftChild;
	free(OldRoot);

	DeletedQueue = Initialize();
	DeletedQueue->CurrentSize = (1 << MinTree) - 1;
	for (int i = MinTree - 1; i >= 0; i--)
	{
		DeletedQueue->TheTrees[i] = DeletedTree;
		DeletedTree = DeletedTree->NextSibling;
		DeletedQueue->TheTrees[i]->NextSibling = NULL;
	}

	BQ->TheTrees[MinTree] = NULL;
	BQ->CurrentSize -= DeletedQueue->CurrentSize + 1;

	Merge(BQ, DeletedQueue);
	return MinItem;
}

BinTree DestroyTree(BinTree T)
{
	BinTree LeftChild, NextSibling;

	if (T)
	{
		LeftChild = T->LeftChild;
		NextSibling = T->NextSibling;
		free(T);
		DestroyTree(NextSibling);
		DestroyTree(LeftChild);
	}

	return NULL;
}

BinQueue MakeEmpty(BinQueue BQ)
{
	for (int i = 0; i < MaxTrees; i++)
		if (BQ->TheTrees[i])
			BQ->TheTrees[i] = DestroyTree(BQ->TheTrees[i]);
	
	free(BQ);
	return NULL;
}

static BinTree InsertIntoTree(ElementType X)
{
	BinTree T;

	T = malloc(sizeof(BinNode));
	if (!T)
	{
		FatalError("Out of space");
		return NULL;
	}
	T->Element = X;
	T->LeftChild = NULL;
	T->NextSibling = NULL;

	return T;
}

BinQueue Insert(ElementType X, BinQueue BQ)
{
	BinTree newTree;
	int BQIndex = 0;

	if (IsFull(BQ))
		Error("Merge would exceed capacity!\n");
	else
	{
		newTree = InsertIntoTree(X);
		for (int i = 0; i < MaxTrees; i++)
		{
			if (!(BQ->TheTrees[i]))
			{
				BQ->TheTrees[i] = newTree;
				break;
			}
			else
			{
				newTree = CombineTrees(BQ->TheTrees[i], newTree);
				BQ->TheTrees[i] = NULL;
			}
		}
		BQ->CurrentSize++;
	}

	return BQ;
}

ElementType FindMin(BinQueue BQ)
{
	ElementType MinValue;
		
	MinValue = Infinity;
	for (int i = 0; i < MaxTrees; i++)
		if (BQ->TheTrees[i] &&
			Compare(BQ->TheTrees[i]->Element, MinValue) == SMALLER)
			MinValue = BQ->TheTrees[i]->Element;

	return MinValue;
}

void Traverse(BinQueue BQ, void(*pfun)(ElementType X))
{
	for (int i = 0; i < MaxTrees; i++)
	{
		if (BQ->TheTrees[i])
		{
			printf("\nTree %d:", i);
			TraverseTree(BQ->TheTrees[i], pfun);
		}
	}
	printf("\n%d elements.", BQ->CurrentSize);
}

bool IsEmpty(BinQueue BQ)
{
	if (BQ->CurrentSize == 0)
		return true;
	else
		return false;
}

bool IsFull(BinQueue BQ)
{
	if (BQ->CurrentSize == Capacity)
		return true;
	else
		return false;
}

static void TraverseTree(BinTree T, void(*pfun)(ElementType X))
{
	if (T)
	{
		pfun(T->Element);
		TraverseTree(T->NextSibling, pfun);
		TraverseTree(T->LeftChild, pfun);
	}
}