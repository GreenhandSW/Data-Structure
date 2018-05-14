#ifndef _Queue_h

struct QueueRecord;
typedef struct QueueRecord * Queue;
typedef int ElementType;

int IsEmpty(Queue Q);
int IsFull(Queue Q);
Queue CreateQueue(int MaxElements);
void DisposeQueue(Queue Q);
void MakeEmpty(Queue Q);
void EnQueue(ElementType X, Queue Q);
ElementType Front(Queue Q);
void DeQueue(Queue Q);
ElementType FrontAndDeQueue(Queue Q);
void PrintQueue(Queue Q);
#endif // !_Queue_h