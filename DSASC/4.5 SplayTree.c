#include<stdio.h>
#include<stdlib.h>
#include"4.5 SplayTree.h"
#include"../Library/General.h"
#include"../Library/s_and_r.h"

/*	printf("%d is already in the tree!\n", X);
	printf("%d not found!\n", X);
	return X > Y ? X : Y;
	printf("%d is not in the tree!\n", X);
	These lines has to be modified is ElementType changed
*/

struct AvlNode
{
	ElementType Element;
	AvlTree Left;
	AvlTree Right;
	int Height;
};

static Position SingleRotateWithLeft(Position K2);
static Position SingleRotateWitRight(Position K1);
static Position ZigZagLeft(Position K3);
static Position ZigZagRight(Position K1);
static Position ZigZigLeft(Position K3);
static Position ZigZigRight(Position K1);
static ElementType MAX(ElementType X, ElementType Y);
// Compares two elements a and b. For standard correspondence of char and other types,
// 0 is the same, -1 is a<b, and 1 is a>b
int
Compare(ElementType a, ElementType b)
{
	if (a == b)
		return EQUAL;
	else if (a < b)
		return SMALLER;
	else
		return BIGGER;
}

static int
Height(Position P)
{
	if (P == NULL)
		return -1;
	else
		return P->Height;
}

AvlTree
MakeEmpty(AvlTree T)
{
	if (T)
	{
		MakeEmpty(T->Left);
		MakeEmpty(T->Right);
		free(T);
	}

	return NULL;
}

// find X and splay the tree
Position
Find(ElementType X, AvlTree T)
{
	return T;
	// implement this while not busy.
}

Position
FindMin(AvlTree T)
{
	if (T)
		while (T->Left)
			T = T->Left;

	return T;
}

Position
FindMax(AvlTree T)
{
	if (T)
		while (T->Right)
			T = T->Right;

	return T;
}

AvlTree
Insert(ElementType X, AvlTree T)
{
	if (!T)
	{
		// Create and return a one-node tree;
		T = malloc(sizeof(AvlNode));
		if (!T)
			FatalError("Out of space!!!\n");
		else
		{
			T->Element = X;
			T->Height = 0;
			T->Left = NULL;
			T->Right = NULL;
		}
	}
	else if (Compare(X, T->Element) == SMALLER)
		T->Left = Insert(X, T->Left);
	else if (Compare(X, T->Element) == BIGGER)
		T->Right = Insert(X, T->Right);
	// Else X is already in the tree, we'll do nothing
	else
		printf("%d is already in the tree!\n", X);

	T->Height = MAX(Height(T->Left), Height(T->Right)) + 1;
	return T;
}

AvlTree
Delete(ElementType X, AvlTree T)
{
	Position TmpCell;

	if (T == NULL)
		printf("%d not found!\n", X);
	else if (Compare(X, T->Element) == SMALLER)	// Go left
		T->Left = Delete(X, T->Left);
	else if (Compare(X, T->Element) == BIGGER)	// Go right
		T->Right = Delete(X, T->Right);
	else if (T->Left && T->Right)	// Found element to be deleted
	{
		int choice = Random(0, 2);

		// Replace with smallest in right tree
		if (choice == LEFT)
		{
		TmpCell = FindMin(T->Right);
		T->Element = TmpCell->Element;
		T->Right = Delete(T->Element, T->Right);
		}
		// Replace with biggest in left tree
		else if (choice == RIGHT)
		{
			TmpCell = FindMax(T->Left);
			T->Element = TmpCell->Element;
			T->Left = Delete(T->Element, T->Left);
		}
	}
	else	// One or zero children
	{
		TmpCell = T;
		if (T->Left == NULL)	// Also handles 0 children
			T = T->Right;
		else if (T->Right == NULL)
			T = T->Left;
		free(TmpCell);
	}

	return T;
}

static Position
SingleRotateWithLeft(Position K2)
{
	Position K1 = K2->Left;
	K2->Left = K1->Right;
	K1->Right = K2;

	K2->Height = MAX(Height(K2->Left), Height(K2->Right)) + 1;
	K1->Height = MAX(Height(K1->Left), Height(K2)) + 1;

	return K1;	// new root
}

static Position
SingleRotateWitRight(Position K1)
{
	Position K2 = K1->Right;

	K1->Right = K2->Left;
	K2->Left = K1;
	K1->Height = MAX(Height(K1->Left), Height(K1->Right)) + 1;
	K2->Height = MAX(Height(K2->Left), Height(K2->Right)) + 1;

	return K2;	// new root
}

static Position
ZigZagLeft(Position K3)
{
	Position K1 = K3->Left;
	Position K2 = K1->Right;

	K1->Right = K2->Left;
	K3->Left = K2->Right;
	K2->Left = K1;
	K2->Right = K3;
	K1->Height = MAX(Height(K1->Left), Height(K1->Right)) + 1;
	K3->Height = MAX(Height(K3->Left), Height(K3->Right)) + 1;
	K2->Height = MAX(Height(K2->Left), Height(K2->Right)) + 1;

	return K2;
}

static Position
ZigZagRight(Position K1)
{
	Position K3 = K1->Right;
	Position K2 = K3->Left;

	K1->Right = K2->Left;
	K3->Left = K2->Right;
	K2->Left = K1;
	K2->Right = K3;
	K1->Height = MAX(Height(K1->Left), Height(K1->Right)) + 1;
	K3->Height = MAX(Height(K3->Left), Height(K3->Right)) + 1;
	K2->Height = MAX(Height(K2->Left), Height(K2->Right)) + 1;

	return K2;
}

Position ZigZigLeft(Position K3)
{
	Position K2 = K3->Left;
	Position K1 = K2->Left;
	
	K3->Left = K2->Right;
	K2->Right = K3;
	K2->Left = K1->Right;
	K1->Right = K2;
	K3->Height = MAX(Height(K3->Left), Height(K3->Right)) + 1;
	K2->Height = MAX(Height(K2->Left), Height(K2->Right)) + 1;
	K1->Height = MAX(Height(K1->Left), Height(K1->Right)) + 1;

	return K1;
}

Position ZigZigRight(Position K1)
{
	Position K2 = K1->Right;
	Position K3 = K2->Right;

	K1->Right = K2->Left;
	K2->Left = K1;
	K2->Right = K3->Left;
	K3->Left = K2;
	K1->Height = MAX(Height(K1->Left), Height(K1->Right)) + 1;
	K2->Height = MAX(Height(K2->Left), Height(K2->Right)) + 1;
	K3->Height = MAX(Height(K3->Left), Height(K3->Right)) + 1;

	return K1;
}

// has to be modified if ElementType is changed
static ElementType
MAX(ElementType X, ElementType Y)
{
	return X > Y ? X : Y;
}

ElementType
Retrieve(Position P)
{
	return P->Element;
}

void PreOrder(AvlTree T, void(*pfun)(ElementType X))
{
	if (T)
	{
		(*pfun)(T->Element);
		PreOrder(T->Left, pfun);
		PreOrder(T->Right, pfun);
	}
}

void InOrder(AvlTree T, void(*pfun)(ElementType X))
{
	if (T)
	{
		InOrder(T->Left, pfun);
		(*pfun)(T->Element);
		InOrder(T->Right, pfun);
	}
}

void PostOrder(AvlTree T, void(*pfun)(ElementType X))
{
	if (T)
	{
		PostOrder(T->Left, pfun);
		PostOrder(T->Right, pfun);
		(*pfun)(T->Element);
	}
}