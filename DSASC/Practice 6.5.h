#ifndef _Binary_Heap_H

#include<stdbool.h>

#define Infinity 2147483647
#define MinData -100
#define MaxData 10000
typedef int ElementType;
typedef int Position;
typedef struct HeapStruct HeapStruct;
typedef HeapStruct * PriorityQueue;

// Initialize PriorityQueue with list[Length]
PriorityQueue Initialize(ElementType list[], int Length);
void Destroy(PriorityQueue Q);
PriorityQueue MakeEmpty(PriorityQueue Q);
void Insert(ElementType X, PriorityQueue Q);
ElementType DeleteMin(PriorityQueue Q);
ElementType FindMin(PriorityQueue Q);
bool IsFull(PriorityQueue Q);
bool IsEmpty(PriorityQueue Q);
void Traverse(PriorityQueue Q, void(*pfun)(ElementType X));
void PercolateUp(PriorityQueue Q, Position P);
void PercolateDown(PriorityQueue Q, Position P);
void DecreaseKey(Position P, ElementType Delta, PriorityQueue Q);
void IncreaseKey(Position P, ElementType Delta, PriorityQueue Q);
ElementType Delete(Position P, PriorityQueue Q);
// Build a heap with the initialized array in PriorityQueue.
void BuildHeap(PriorityQueue Q);
int GetCurSize(PriorityQueue Q);
ElementType GetValue(Position P, PriorityQueue Q);
void FindSmaller(ElementType X, PriorityQueue Q, void (*pfun)(ElementType X));

void PrintElement(ElementType X);

#endif // !_Binary_Heap_H