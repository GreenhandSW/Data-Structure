#pragma once
#ifndef _TREE_H

typedef int ElementType;
typedef struct TreeNode TreeNode;
typedef struct TreeHead TreeHead;
typedef TreeHead * TreeHeadPtr;
typedef TreeNode * Position;
typedef TreeNode * SearchTree;
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
TreeHeadPtr MakeTreeEmpty(TreeHeadPtr THP);		// doesn't free the space of TreeHead
Position Find(ElementType X, TreeHeadPtr THP);
Position FindMin(TreeHeadPtr THP);
Position FindMax(TreeHeadPtr THP);
Position FindMinOrMax(TreeHeadPtr THP);
SearchTree Delete(ElementType X, TreeHeadPtr THP);
void PreOrder(void(*pfun)(ElementType X), TreeHeadPtr THP);
void InOrder(void(*pfun)(ElementType X), TreeHeadPtr THP);
void PostOrder(void(*pfun)(ElementType X), TreeHeadPtr THP);
Position Insert(ElementType X, TreeHeadPtr THP);
int GetSearchTreeSize(TreeHeadPtr THP);

SearchTree subMakeTreeEmpty(SearchTree T);
Position subFind(ElementType X, SearchTree T);
Position subFindMin(SearchTree T);
Position subFindMax(SearchTree T);
SearchTree subDelete(ElementType X, SearchTree T, int * TSize);
// randomly return the position of min or max, 
// and use it in Delete Process when T has 2 children.
Position subFindMinOrMax(SearchTree T);
void subPreOrder(SearchTree T, void (*pfun)(ElementType X));
void subInOrder(SearchTree T, void(*pfun)(ElementType X));
void subPostOrder(SearchTree T, void(*pfun)(ElementType X));
ElementType Retrieve(Position P);

#endif // !_TREE_H