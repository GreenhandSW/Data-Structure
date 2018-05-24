#include<stdio.h>
#include<stdlib.h>
#include"../Library/General.h"
#include"5.3 HashTable Separate Chaining.h"

#define MinTableSize 7
typedef unsigned int Index;

struct ListNode
{
	ElementType Element;
	Position Next;
};

struct HashTbl
{
	int TableSize;
	int CurrentNum;
	List * Lists;
};

// Compares two elements a and b,
// has to be modified if ElementType is changed.
int
Compare(ElementType a, ElementType b)
{
	if (a&&b)
		return strcmp(a, b);
	else if (!a)
		return SMALLER;
	else
		return BIGGER;
}

// calculate ¦² Key(i=0~KeySize-1) [KeySize-i-1]¡¤32^i
// by Law of Hornor
Index Hash(ElementType Key, int TableSize)
{
	unsigned int HashVal = 0;

	while (*Key != '\0')
		HashVal = (HashVal << 5) + *(Key++);

	return HashVal % TableSize;
}

HashTable InitializeTable(int TableSize)
{
	HashTable H;

	if (TableSize < MinTableSize)
	{
		Error("Table size too small!\n");
		return NULL;
	}

	// Allocate table
	H = malloc(sizeof(HashTbl));
	if (!H)
		FatalError("Out of space!!!\n");

	H->TableSize = NextPrime(TableSize);
	H->CurrentNum = 0;

	// Allocate array of lists
	H->Lists = malloc(sizeof(List) * H->TableSize);
	if (H->Lists == NULL)
		FatalError("Out of space!!!\n");

	// Allocate list headers
	for (int i = 0; i < H->TableSize; i++)
	{
		H->Lists[i] = malloc(sizeof(ListNode));
		if (H->Lists[i] == NULL)
			FatalError("Out of space!!!\n");
		else
		{
			H->Lists[i]->Next = NULL;
			H->Lists[i]->Element = NULL;
		}
	}

	return H;
}

HashTable MakeEmpty(HashTable H)
{
	DestroyTable(H);
	free(H->Lists);
	free(H);

	return NULL;
}

void DestroyTable(HashTable H)
{
	for (int i = 0; i < H->TableSize; i++)
	{
		List L = H->Lists[i];
		while (L)
		{
			L = L->Next;
			free(L);
		}
	}
	H->CurrentNum = 0;
}

Position Find(ElementType Key, HashTable H)
{
	Position P;
	List L;

	L = H->Lists[Hash(Key, H->TableSize)];
	P = L->Next;
	while (P && Compare(P->Element, Key) != EQUAL)
		P = P->Next;

	return P;
}

void Delete(ElementType Key, HashTable H)
{
	List * L;
	List tmp;

	L = &(H->Lists[Hash(Key, H->TableSize)]);
	while ((*L) && Compare((*L)->Element, Key) != EQUAL)
		L = &((*L)->Next);
	tmp = *L;
	(*L) = (*L)->Next;
	free(tmp);
	H->CurrentNum--;
}

void Insert(ElementType Key, HashTable H)
{
	Position NewCell;
	List L;

	// HashTable doesn't need to record the frequency
	// of the existence of values, so if we found key
	// in the table, we'd do nothing.
	if (!Find(Key, H))	// Key is not found
	{
		NewCell = malloc(sizeof(ListNode));
		if (!NewCell)
			FatalError("Out of space!!!\n");
		else
		{
			L = H->Lists[Hash(Key, H->TableSize)];
			NewCell->Next = L->Next;
			NewCell->Element = Key;	// Probably need strcpy!
			L->Next = NewCell;
			H->CurrentNum++;
		}
	}
}

ElementType Retrieve(Position P)
{
	if (P)
		return P->Element;
	return NULL;
}

void Traverse(HashTable H, void(*pfun)(ElementType X))
{
	for (int i = 0; i < H->TableSize; i++)
	{
		List L = H->Lists[i];
		if (L);
			puts("");
		while (L)
		{
			pfun(L->Element);
			L = L->Next;
		}
	}
}

int GetSize(HashTable H)
{
	return H->TableSize;
}

int GetCurrentCount(HashTable H)
{
	return H->CurrentNum;
}
