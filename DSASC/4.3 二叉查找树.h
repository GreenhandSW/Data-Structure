#pragma once
#ifndef _TREE_H

typedef int ElementType;
typedef struct TreeNode TreeNode;
typedef TreeNode * Position;
typedef TreeNode * SearchTree;

SearchTree MakeEmpty(SearchTree T);
Position Find(ElementType X, SearchTree T);
Position FindMin(SearchTree T);
Position FindMax(SearchTree T);
// randomly return the position of min or max, 
// and use it in Delete Process when T has 2 children.
Position FindMinOrMax(SearchTree T);
Position Insert(ElementType X, SearchTree * T);
void Delete(ElementType X, SearchTree T);
void PreOrder(SearchTree T, void (*pfun)(ElementType X));
void InOrder(SearchTree T, void(*pfun)(ElementType X));
void PostOrder(SearchTree T, void(*pfun)(ElementType X));
ElementType Retrieve(Position P);

#endif // !_TREE_H