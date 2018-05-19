#include<stdio.h>
#include"4.4 AvlTree.h"
#include"../Library/General.h"

struct AvlNode
{
	ElementType Element;
	AvlTree Left;
	AvlTree Right;
	int Height;
};

// Compares two elements a and b. For standard correspondence of char and other types,
// 0 is the same, -1 is a<b, and 1 is a>b
int Compare(ElementType a, ElementType b)
{
	if (a == b)
		return EQUAL;
	else if (a < b)
		return SMALLER;
	else
		return BIGGER;
}

static int Height(Position P)
{
	if (P == NULL)
		return -1;
	else
		return P->Height;
}

AvlTree Insert(ElementType X, AvlTree * T)
{
	while (*T)
	{

	}
}