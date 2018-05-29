#ifndef _Leftist_Heap_H

#include<stdbool.h>

#define MinData -100
#define MaxData 10000

typedef int ElementType;
typedef struct BinNode BinNode;
typedef BinNode * BinTree;
typedef BinNode * Position;
typedef struct Collection Collection;
typedef Collection * BinQueue;

BinQueue Initialize(void);
BinQueue Merge(BinQueue BQ1, BinQueue BQ2);
ElementType DeleteMin(BinQueue BQ);
BinQueue MakeEmpty(BinQueue BQ);
BinQueue Insert(ElementType X, BinQueue BQ);
ElementType FindMin(BinQueue BQ);
void Traverse(BinQueue BQ, void(*pfun)(ElementType X));
bool IsEmpty(BinQueue BQ);
bool IsFull(BinQueue BQ);

#endif // !_Leftist_Heap_H