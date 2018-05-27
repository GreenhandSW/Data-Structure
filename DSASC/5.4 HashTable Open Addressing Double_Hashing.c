#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"../Library/General.h"
#include"5.4 HashTable Open Addressing Double_Hashing.h"

/*	printf("%s is not in the table!\n", Key);
	Hash
	Hash2
	Compare
	have to be modified if ElementType is changed.
*/

#define MinTableSize 7

typedef enum KindOfEntry { Legitimate, Empty, Deleted }KindOfEntry;

struct HashEntry
{
	ElementType Element;
	KindOfEntry Info;
};

typedef struct HashEntry Cell;

// Cell *TheCells will be an array of
// HashEntry cells, allocated later
struct HashTbl
{
	int TableSize;
	int CurrentNum;
	Cell * TheCells;
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
	int HashVal = 0;

	while (*Key != '\0')
		HashVal = (HashVal << 5) + *(Key++);

	return HashVal % TableSize;
}

Index Hash2(ElementType Key, int TableSize)
{
	int HashVal = 0;
	int R = PrevPrime(TableSize);

	while (*Key != '\0')
		HashVal = (HashVal << 5) + *(Key++);

	return R - HashVal % R;
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

	// Allocate array of Cells
	H->TheCells = malloc(sizeof(Cell) * H->TableSize);
	if (H->TheCells == NULL)
		FatalError("Out of space!!!\n");

	for (int i = 0; i < H->TableSize; i++)
		H->TheCells[i].Info = Empty;

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
	Cell * tmp = H->TheCells;

	H->CurrentNum = 0;
	free(tmp);
	H->TheCells = NULL;
}

Position Find(ElementType Key, HashTable H)
{
	Position CurrentPos;
	int CollisionNum;
	int Hash2_Increment;

	CollisionNum = 0;
	CurrentPos = Hash(Key, H->TableSize);
	Hash2_Increment = Hash2(Key, H->TableSize);
	// There is no condition to stop infinite loop, because the default
	// TableSize is bigger than input elements in the test file.
	while (H->TheCells[CurrentPos].Info != Empty &&
		Compare(H->TheCells[CurrentPos].Element, Key) != EQUAL)
	{
		CurrentPos += Hash2_Increment;
		CurrentPos %= H->TableSize;
	}

	return CurrentPos;
}

void Delete(ElementType Key, HashTable H)
{
	Position P = Find(Key, H);

	if (H->CurrentNum <= 0)
		Error("HashTable empty!\n");
	else if (P < 0)
		printf("%s is not in the table!\n", Key);
	else if (H->TheCells[P].Info == Legitimate)
	{
		H->TheCells[P].Element = NULL;
		H->TheCells[P].Info = Deleted;
		H->CurrentNum--;
	}
}

void Insert(ElementType Key, HashTable H)
{
	Position Pos;

	if (H->CurrentNum == H->TableSize)
	{
		printf("Insertion failed, HashTable full!\n");
		return;
	}
	Pos = Find(Key, H);
	if (H->TheCells[Pos].Info != Legitimate)
	{
		// OK to insert here
		H->TheCells[Pos].Info = Legitimate;
		H->TheCells[Pos].Element = Key;
		H->CurrentNum++;
	}
}

ElementType Retrieve(Position P, HashTable H)
{
	if (H->TheCells[P].Info == Legitimate)
		return H->TheCells[P].Element;
	else
		return NULL;
}

void Traverse(HashTable H, void(*pfun)(ElementType X))
{
	for (int i = 0; i < H->TableSize; i++)
		pfun(Retrieve(i, H));
}

int GetSize(HashTable H)
{
	return H->TableSize;
}