/*	printf("%d is already in the Tree!\n", X);
	printf("%d is not in the tree!", X);
	these lines has to be rewritten if ElementType is changed
*/
#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include"4.3 二叉查找树.h"
#include"../Library/通用.h"
#include"../Library/s_and_r.h"
#define LEFT 0
#define RIGHT 1
struct TreeNode
{
	ElementType Element;
	SearchTree Left;
	SearchTree Right;
};

struct TREEHEAD
{
	SearchTree T;
	int n;
};
// make new node with value x
SearchTree MakeNewNode(ElementType X, SearchTree T);
// delete node which has only 1 child.
SearchTree DeleteOne(ElementType X, SearchTree T);

// make tree empty with post-order traversal
SearchTree
MakeEmpty(SearchTree T)
{
	if (T!=NULL)
	{
		MakeEmpty(T->Left);
		MakeEmpty(T->Right);
		free(T);
	}
	return NULL;
}

// recursively find x
Position
Find(ElementType X, SearchTree T)
{
	if (!T)
		return NULL;

	if (X < T->Element)
		Find(X, T->Left);
	else if (X > T->Element)
		Find(X, T->Right);

	return T;

	// non-recursively find x
	//while (T)
	//{
	//	if (X < T->Element)
	//		T = T->Left;
	//	else if (X > T->Element)
	//		T = T->Right;
	//	else
	//		break;
	//}

	//return T;
}

Position
FindMin(SearchTree T)
{
	if (T)
		while (T->Left)
			T = T->Left;

	return T;
}

Position
FindMax(SearchTree T)
{
	if (T)
		while (T->Right)
			T = T->Right;

	return T;
}

Position FindMinOrMax(SearchTree T)
{
	if (Random(0, 2) == 1)
		return FindMin(T);
	else
		return FindMax(T);
}

Position
Insert(ElementType X, SearchTree T)
{
	TreeNode * T;

	while (T)
	{
		if (X < T->Element)
			T = T->Left;
		else if (X > T->Element)
			T = T->Right;
		// else X is already in the Tree, we'll raise error and return NULL
		else
		{
			printf("%d is already in the Tree!\n", X);
			return T;
		}
	}

	T = (TreeNode *)malloc(sizeof(TreeNode));
	if (!T)
	{
		FatalError("Out of space!!!");
		MakeEmpty(T);
		exit(1);
	}
	T->Element = X;
	T->Left = NULL;
	T->Right = NULL;

	return T;
}

TreeNode * MakeNewNode(ElementType X, SearchTree T)
{
	TreeNode * node;
	
	node = (TreeNode *)malloc(sizeof(TreeNode));
	if (!node)
	{
		FatalError("Out of space!!!");
		MakeEmpty(T);
		exit(1);
	}
	node->Element = X;
	node->Left = NULL;
	node->Right = NULL;
	return node;
}

SearchTree DeleteOne(ElementType X, SearchTree T)
{
	Position TmpCell = T;
	if (T->Right)
		T = T->Right;
	else if (T->Left)
		T = T->Left;
	free(TmpCell);

	return T;
}

void
Delete(ElementType X, SearchTree T)
{
	Position TmpCell;

	while (T)
	{
		if (X < T->Element)
			T = T->Left;
		else if (X > T->Element)
			T = T->Right;
		else if (T->Left && T->Right)	// two children
		{
			int choice = Random(0, 2);
			if (choice == LEFT)
			{
				TmpCell = FindMin(T->Right);
				T->Element = TmpCell->Element;
				T->Right = DeleteOne(X, T->Right);
			}
			else if (choice == RIGHT)
			{
				TmpCell = FindMax(T->Left);
				T->Element = TmpCell->Element;
				T->Left = DeleteOne(X, T->Left);
			}
			else
			{
				printf("%d is not in the tree!", X);
				break;
			}
		}
		else
			DeleteOne(X, T);
	}
}

void PreOrder(SearchTree T, void(*pfun)(ElementType X))
{
	if (T)
	{
		(*pfun)(T->Element);
		PreOrder(T->Left, pfun);
		PreOrder(T->Right, pfun);
	}
}

void InOrder(SearchTree T, void(*pfun)(ElementType X))
{
	if (T)
	{
		InOrder(T->Left, pfun);
		(*pfun)(T->Element);
		InOrder(T->Right, pfun);
	}
}

void PostOrder(SearchTree T, void(*pfun)(ElementType X))
{
	if (T)
	{
		PostOrder(T->Left, pfun);
		PostOrder(T->Right, pfun);
		(*pfun)(T->Element);
	}
}
ElementType Retrieve(Position P)
{
	return P->Element;
}
