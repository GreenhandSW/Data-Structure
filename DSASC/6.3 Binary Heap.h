#ifndef _Binary_Heap_H

#include<stdbool.h>

#define MinData -100
#define MaxData 10000
typedef int ElementType;
typedef struct HeapStruct HeapStruct;
typedef HeapStruct * PriorityQueue;

PriorityQueue Initialize(int MaxElements);
void Destroy(PriorityQueue Q);
PriorityQueue MakeEmpty(PriorityQueue Q);
void Insert(ElementType X, PriorityQueue Q);
ElementType DeleteMin(PriorityQueue Q);
ElementType FindMin(PriorityQueue Q);
bool IsFull(PriorityQueue Q);
bool IsEmpty(PriorityQueue Q);
void Traverse(PriorityQueue Q, void(*pfun)(ElementType X));

#endif // !_Binary_Heap_H