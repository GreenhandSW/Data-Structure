#ifndef _Leftist_Heap_H

#include<stdbool.h>

#define MinData -100
#define MaxData 10000
typedef int ElementType;
typedef struct TreeNode TreeNode;
typedef TreeNode * PriorityQueue;

// Minimal set of priority queue operations
// Note that nodes will be shared among several
// leftist heaps after a merge, the user must
// make sure to not use the old leftist heaps;

#define Insert(X, Q) (Q = Insert1((X), Q))
//#define DeleteMin(Q) ((FindMin(Q))

PriorityQueue Initialize(void);
ElementType FindMin(PriorityQueue Q);
bool IsEmpty(PriorityQueue Q);
PriorityQueue Merge(PriorityQueue Q1, PriorityQueue Q2);
PriorityQueue MakeEmpty(PriorityQueue Q);

PriorityQueue Insert1(ElementType X, PriorityQueue Q);
PriorityQueue DeleteMin1(PriorityQueue Q);
void Traverse(PriorityQueue Q, void(*pfun)(ElementType X));
#endif // !_Leftist_Heap_H