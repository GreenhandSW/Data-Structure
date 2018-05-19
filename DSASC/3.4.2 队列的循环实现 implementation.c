#include<stdio.h>
#include<stdlib.h>
#include"../Library/General.h"
#include"3.4.2 队列的循环实现 Queue.h"

/* Place in implementation file */
/* Queue implementation is a dynamically allocated array */
#define MinQueueSize (5)

struct QueueRecord
{
	int Capacity;
	int Front;
	int Rear;
	int Size;
	ElementType * Array;
};

int
IsEmpty(Queue Q)
{
	return Q->Size == 0;
}

int
IsFull(Queue Q)
{
	return Q->Size == Q->Capacity;
}

void
MakeEmpty(Queue Q)
{
	Q->Size = 0;
	Q->Front = 1;
	Q->Rear = 0;
}

static int 
Succ(int Value, Queue Q)
{
	if (++Value == Q->Capacity)
		Value = 0;
	return Value;
}

void
EnQueue(ElementType X, Queue Q)
{
	if (IsFull(Q))
		Error("Full queue");
	else
	{
		Q->Size++;
		Q->Rear = Succ(Q->Rear, Q);
		Q->Array[Q->Rear] = X;
	}
}

void
DeQueue(Queue Q)
{
	if (IsEmpty(Q))
		Error("Empty queue");
	else
	{
		Q->Size--;
		Q->Front = Succ(Q->Front, Q);
	}
}

ElementType
Front(Queue Q)
{
	if(!IsEmpty(Q))
		return Q->Array[Q->Front];
	Error("Empty queue");
	return 0;
}

ElementType
FrontAndDeQueue(Queue Q)
{
	if (!IsEmpty(Q))
	{
		ElementType front = Q->Array[Q->Front];
		Q->Size--;
		Q->Front = Succ(Q->Front, Q);
		return front;
	}
	Error("Empty queue");
	return 0;
}

Queue CreateQueue(int MaxElements)
{
	Queue Q;

	if (MaxElements < MinQueueSize)
		Error("Queue size is too small");

	Q = malloc(sizeof(struct QueueRecord));
	if (Q == NULL)
		FatalError("Out of space!!!");

	Q->Array = (ElementType *)malloc(sizeof(ElementType)*MaxElements);
	if (Q->Array == NULL)
		FatalError("Out of space!!!");
	Q->Capacity = MaxElements;
	MakeEmpty(Q);

	return Q;
}

void
DisposeQueue(Queue Q)
{
	if (Q != NULL)
	{
		free(Q->Array);
		free(Q);
	}
}

void
PrintQueue(Queue Q)
{
	if (!IsEmpty(Q))
	{
		int front = Q->Front;
		int rear = Q->Rear;
		int size = Q->Size;

		// print from front to rear
		//while (!(size == 0))
		//{
		//	if (!IsEmpty(Q))
		//		printf("%5d ", Q->Array[front]);
		//	size--;
		//	front = Succ(front, Q);
		//}

		// print by the way the numbers actually stored in the array
		if (rear < front)
		{
			for (int i = 0; i < Q->Capacity; i++)
			{
				if (i > rear && i < front)
					printf("      ");
				else
					printf("%5d ", Q->Array[i]);
			}
		}
		else
			for (int i = 0; i <= rear; i++)
			{
				if (i < front)
					printf("      ");
				else
					printf("%5d ", Q->Array[i]);
			}

		puts("");
	}
	else
		Error("Empty queue\n");
}