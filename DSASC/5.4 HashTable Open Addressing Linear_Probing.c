#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include"../Library/General.h"
#include"5.4 HashTable Open Addressing Linear_Probing.h"

/*	printf("%s is not in the table!\n", Key);
	printf("%s is already in the Table!\n", Key);
	pfun(Retrieve(&(H->Lists[i])));	// This is redundant, but as for any other
	Hash
	Compare
	have to be modified if ElementType is changed.
*/

#define MinTableSize 7
typedef unsigned int Index;

bool CellIsEmpty(ElementType X)
{
	return X == NULL;
}

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

	// Assign list headers
	for (int i = 0; i < H->TableSize; i++)
		H->Lists[i] = NULL;

	return H;
}

HashTable MakeEmpty(HashTable H)
{
	DestroyTable(H);
	free(H);

	return NULL;
}

void DestroyTable(HashTable H)
{
	List * tmp = H->Lists;
	free(tmp);
	H->Lists = NULL;
}

Position Find(ElementType Key, HashTable H)
{
	int start;
	int index;

	if (!Key)
		return NULL;
	start = Hash(Key, H->TableSize);
	for (index = 0; index < H->TableSize; index++)
	{
		if (Compare(H->Lists[start], Key) == EQUAL)
			break;
		else
		{
			start++;
			start %= H->TableSize;
		}
	}
	if (index == H->TableSize)
	{
		//printf("%s is not in the table!\n", Key);
		return NULL;
	}
	else
		return &(H->Lists[start]);
}

void Delete(ElementType Key, HashTable H)
{
	Position P = Find(Key, H);

	if (P)
	{
		*P = NULL;
		H->CurrentNum--;
	}
	else
		printf("%s is not in the table!\n", Key);
}

void Insert(ElementType Key, HashTable H)
{
	int start = Hash(Key, H->TableSize);

	// HashTable is full
	if (H->CurrentNum == H->TableSize)
		puts("Insertion failed, HashTable full!!!");
	else if (Find(Key, H) != NULL)
		printf("%s is already in the Table!\n", Key);
	else	// find a vacancy to put Key into.
		for (int i = 0; i < H->CurrentNum + 1; i++)	// There's CurrentNum element in the list
		{											// so if we try CurrentNum + 1 times, we must find a vacancy.
			if (CellIsEmpty(H->Lists[start]))
			{
				H->Lists[start] = Key;
				H->CurrentNum++;
				break;
			}
			else
			{
				start++;
				start %= H->TableSize;
			}
		}
}

ElementType Retrieve(Position P)
{
	if (P)
		return *P;
	else
		return NULL;
}

void Traverse(HashTable H, void(*pfun)(ElementType X))
{
	for (int i = 0; i < H->TableSize; i++)
		pfun(Retrieve(&(H->Lists[i])));	// This is redundant, but as for any other
										// ElementType may need "Retrieve" it's value
										// from its node, so it's retained.
}

int GetSize(HashTable H)
{
	return H->TableSize;
}

int GetCurrentCount(HashTable H)
{
	return H->CurrentNum;
}
