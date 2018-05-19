#ifndef _AvlTree_H

typedef struct AvlNode AvlNode;
typedef struct AvlNode * Position;
typedef struct AvlNode * AvlTree;
typedef int ElementType;

AvlTree MakeEmpty(AvlTree T);
Position Find(ElementType X, AvlTree T);
Position FindMin(AvlTree T);
Position FindMax(AvlTree T);
AvlTree Insert(ElementType X, AvlTree T);
AvlTree Delete(ElementType X, AvlTree T);
ElementType Retrieve(Position P);
void PreOrder(AvlTree T, void(*pfun)(ElementType X));
void InOrder(AvlTree T, void(*pfun)(ElementType X));
void PostOrder(AvlTree T, void(*pfun)(ElementType X));


#endif // !_AvlTree_H