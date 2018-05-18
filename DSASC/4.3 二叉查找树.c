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
#define SMALLER -1
#define EQUAL 0
#define BIGGER 1

struct TreeNode
{
	ElementType Element;
	SearchTree Left;
	SearchTree Right;
};

struct TreeHead
{
	SearchTree T;
	int n;
};

// make new node with value x
SearchTree MakeNewNode(ElementType X, SearchTree T);
// delete node which has only 1 child.
//SearchTree DeleteOne(ElementType X, SearchTree * T);
// Compares two elements a and b. For standard correspondence of char and other types,
// 0 is the same, -1 is a<b, and 1 is a>b
int Compare(ElementType a, ElementType b);

// make tree empty with post-order traversal
SearchTree
subMakeTreeEmpty(SearchTree T)
{
	if (T!=NULL)
	{
		subMakeTreeEmpty(T->Left);
		subMakeTreeEmpty(T->Right);
		free(T);
	}
	return NULL;
}

// recursively find x
Position
subFind(ElementType X, SearchTree T)
{
	if (!T)
		return NULL;

	if (Compare(X, T->Element) == SMALLER)
		subFind(X, T->Left);
	else if (Compare(X, T->Element) == BIGGER)
		subFind(X, T->Right);

	return T;

	// non-recursively find x
	//while (T)
	//{
	//	if (Compare(X, T->Element) == SMALLER)
	//		T = T->Left;
	//	else if (Compare(X, T->Element) == BIGGER)
	//		T = T->Right;
	//	else
	//		break;
	//}

	//return T;
}

Position
subFindMin(SearchTree T)
{
	if (T)
		while (T->Left)
			T = T->Left;

	return T;
}

Position
subFindMax(SearchTree T)
{
	if (T)
		while (T->Right)
			T = T->Right;

	return T;
}

Position subFindMinOrMax(SearchTree T)
{
	if (Random(0, 2) == 1)
		return subFindMin(T);
	else
		return subFindMax(T);
}

Position
Insert(ElementType X, TreeHeadPtr THP)
{
	if (THP)
	{
		SearchTree * T = &(THP->T);

		while (*T)
		{
			if (Compare(X, (*T)->Element) == SMALLER)
				T = &((*T)->Left);
			else if (Compare(X, (*T)->Element) == BIGGER)
				T = &((*T)->Right);
			// else X is already in the Tree, we'll raise error and return NULL
			else
			{
				printf("%d is already in the Tree!\n", X);
				return *T;
			}
		}
		*T = (TreeNode *)malloc(sizeof(TreeNode));
		if (!*T)
		{
			FatalError("Out of space!!!");
			subMakeTreeEmpty(*T);
			exit(1);
		}
		(*T)->Element = X;
		(*T)->Left = NULL;
		(*T)->Right = NULL;
		THP->n++;

		return *T;
	}

	return NULL;
}

int GetSearchTreeSize(TreeHeadPtr THP)
{
	if (THP)
		return THP->n;

	return 0;
}

TreeNode * MakeNewNode(ElementType X, SearchTree T)
{
	TreeNode * node;
	
	node = (TreeNode *)malloc(sizeof(TreeNode));
	if (!node)
	{
		FatalError("Out of space!!!");
		subMakeTreeEmpty(T);
		exit(1);
	}
	node->Element = X;
	node->Left = NULL;
	node->Right = NULL;
	return node;
}

SearchTree subDelete(ElementType X, SearchTree T, int * TSize)
{
	Position TmpCell;

	if (T == NULL)
		Error("Element not found\n");
	else if (Compare(X, T->Element) == SMALLER)	// Go left
		T->Left = subDelete(X, T->Left, TSize);
	else if (Compare(X, T->Element) == BIGGER)	// Go right
		T->Right = subDelete(X, T->Right, TSize);
	else if (T->Left && T->Right)	// Found element to be deleted
	{
		//int choice = Random(0, 2);

		//// Replace with smallest in right subtree
		//if (choice == LEFT)
		//{
			TmpCell = subFindMin(T->Right);
			T->Element = TmpCell->Element;
			T->Right = subDelete(T->Element, T->Right, TSize);
		//}
		//// Replace with biggest in left subtree
		//else if (choice == RIGHT)
		//{
		//	TmpCell = subFindMax(T->Left);
		//	T->Element = TmpCell->Element;
		//	T->Left = subDelete(T->Element, T->Left, TSize);
		//}
	}
	else	// One or zero children
	{
		TmpCell = T;
		if (T->Left == NULL)	// Also handles 0 children
			T = T->Right;
		else if (T->Right == NULL)
			T = T->Left;
		(*TSize)--;
		free(TmpCell);
	}

	return T;
}
//SearchTree DeleteOne(ElementType X, SearchTree * T)
//{
//	Position TmpCell = *T;
//
//	while(*T && Compare((*T)->Element,X)!=EQUAL)
//	{
//		if(Compare((*T)->Element, X)==BIGGER)
//
//	}
//
//
//	TmpCell = (*T);
//
//	if ((*T)->Left)
//		(*T) = (*T)->Left;
//	else
//		(*T) = (*T)->Right;
//	free(TmpCell);
//
//	return *T;
//}

int Compare(ElementType a, ElementType b)
{
	if (a == b)
		return EQUAL;
	else if (a < b)
		return SMALLER;
	else
		return BIGGER;
}

SearchTree
Delete(ElementType X, TreeHeadPtr THP)
{
	THP->T = subDelete(X, THP->T, &(THP->n));
	return THP->T;

//	if (THP)
//	{
//		SearchTree * T = &(THP->T);
//		Position TmpCell;
//		while (*T)
//		{
//			if (Compare(X, (*T)->Element) == SMALLER)
//				T = &((*T)->Left);
//			else if (Compare(X, (*T)->Element) == BIGGER)
//				T = &((*T)->Right);
//			else if ((*T)->Left && (*T)->Right)	// two children
//			{
//				int choice = Random(0, 2);
//				if (choice == LEFT)
//				{
//					TmpCell = subFindMin((*T)->Right);
//					(*T)->Element = TmpCell->Element;
//					(*T)->Right = DeleteOne(TmpCell->Element, &((*T)->Right));
//				}
//				else if (choice == RIGHT)
//				{
//					TmpCell = subFindMax((*T)->Left);
//					(*T)->Element = TmpCell->Element;
//					(*T)->Left = DeleteOne(TmpCell->Element, &((*T)->Left));
//				}
//				else
//				{
//					printf("%d is not in the tree!", X);
//					return 0;
//				}
//				THP->n--;
//				return 1;
//			}
//			else
//			{
//				DeleteOne(X, T);
//				THP->n--;
//				return 1;
//			}
//		}
//	}
//
//	return 0;
}

void subPreOrder(SearchTree T, void(*pfun)(ElementType X))
{
	if (T)
	{
		(*pfun)(T->Element);
		subPreOrder(T->Left, pfun);
		subPreOrder(T->Right, pfun);
	}
}

void subInOrder(SearchTree T, void(*pfun)(ElementType X))
{
	if (T)
	{
		subInOrder(T->Left, pfun);
		(*pfun)(T->Element);
		subInOrder(T->Right, pfun);
	}
}

void subPostOrder(SearchTree T, void(*pfun)(ElementType X))
{
	if (T)
	{
		subPostOrder(T->Left, pfun);
		subPostOrder(T->Right, pfun);
		(*pfun)(T->Element);
	}
}
ElementType Retrieve(Position P)
{
	return P->Element;
}

TreeHeadPtr MakeTreeEmpty(TreeHeadPtr THP)
{
	if (THP)
	{
		if (THP->T)
			subMakeTreeEmpty(THP->T);
	}
	else
	{
		THP = malloc(sizeof(TreeHead));
	}
	THP->T = NULL;
	THP->n = 0;

	return THP;
}

Position Find(ElementType X, TreeHeadPtr THP)
{
	if(THP)
		return subFind(X, THP->T);

	return NULL;
}

Position FindMin(TreeHeadPtr THP)
{
	if(THP)
		return subFindMin(THP->T);

	return NULL;
}

Position FindMax(TreeHeadPtr THP)
{
	if(THP)
		return subFindMax(THP->T);

	return NULL;
}

Position FindMinOrMax(TreeHeadPtr THP)
{
	return subFindMinOrMax(THP->T);
}

void PreOrder(void(*pfun)(ElementType X), TreeHeadPtr THP)
{
	if (THP->T)
		subPreOrder(THP->T, pfun);
}

void InOrder(void(*pfun)(ElementType X), TreeHeadPtr THP)
{
	if (THP->T)
		subInOrder(THP->T, pfun);
}

void PostOrder(void(*pfun)(ElementType X), TreeHeadPtr THP)
{
	if (THP->T)
		subPostOrder(THP->T, pfun);
}
