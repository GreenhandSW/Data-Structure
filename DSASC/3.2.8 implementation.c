#include"3.2.8 Cursor.h"
#include<stdio.h>

void
FatalError(char *information)
{
	printf(information);
}

ElementType
FindPrevious(ElementType X, List L)
{
	Position P, query;

	P = CursorSpace[L].Next;
	query = CursorSpace[P].Next;
	while (query!=0 && CursorSpace[query].Element!= X)
	{
		P = query;
		query = CursorSpace[query].Next;
	}

	return P;
}

void
InitializeCursorSpace(void)
{
	for (size_t i = 0; i < SpaceSize-1; i++)
	{
		CursorSpace[i].Element = 0;
		CursorSpace[i].Next = i+1;
	}
	CursorSpace[SpaceSize - 1].Next = 0;
}

static Position
CursorAlloc(void)
{
	Position P;

	P = CursorSpace[0].Next;
	CursorSpace[0].Next = CursorSpace[P].Next;

	return P;
}

static void
CursorFree(Position P)
{
	CursorSpace[P].Next = CursorSpace[0].Next;
	CursorSpace[0].Next = P;
}

/* Return True if L is empty */
int
IsEmpty(List L)
{
	return CursorSpace[L].Next == 0;
}

/* Return true if P is the last position in list L */
/* Parameter L is unused in this implementation */

int
IsLast(Position P, List L)
{
	return CursorSpace[P].Next == 0;
}

/* Return Position of X in L; 0 if not found */
/* uses a header node */

Position
Find(ElementType X, List L)
{
	Position P;

	P = CursorSpace[L].Next;
	while (P && CursorSpace[P].Element!=X)
	{
		P = CursorSpace[P].Next;
	}

	return P;
}

/* Delete first occurrence of X from a list */
/* assume use of a header node */

void
Delete(ElementType X, List L)
{
	Position P, TmpCell;

	P = FindPrevious(X, L);

	if (!IsLast(P, L))		/* Assumption of header use */
	{						/* X is found; delete it */
		TmpCell = CursorSpace[P].Next;
		CursorSpace[P].Next = CursorSpace[TmpCell].Next;
		CursorFree(TmpCell);
	}
}

/* Insert (after legal position P) */
/* Header implementation assumed */
/* Parameter L is unused in this implementation */

void
Insert(ElementType X, List L, Position P)
{
	Position TmpCell;

	TmpCell = CursorAlloc();
	if (TmpCell == 0)
		FatalError("Out of space!!!");

	CursorSpace[TmpCell].Element = X;
	CursorSpace[TmpCell].Next = CursorSpace[P].Next;
	CursorSpace[P].Next = TmpCell;
}