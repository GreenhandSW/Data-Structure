#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"../Library/General.h"
#include"5.4 HashTable Open Addressing Rehashing.h"

/*	printf("%s is not in the table!\n", Key);
	Hash
	Compare
	have to be modified if ElementType is changed.
*/

// make MinTableSize very small to see Rehash more than once.
#define MinTableSize 5

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

HashTable Rehash(HashTable H)
{
	int OldSize;
	Cell * OldCells;

	OldCells = H->TheCells;
	OldSize = H->TableSize;
	free(H);

	// Get a new empty table
	H = InitializeTable(2 * OldSize);

	for (int i = 0; i < OldSize; i++)
		if (OldCells[i].Info == Legitimate)
			Insert(OldCells[i].Element, H);

	free(OldCells);
	return H;
}

HashTable InitializeTable(int TableSize)
{
	HashTable H;

	if (TableSize < MinTableSize)
	{
		Error("Table size too small!\n");
		exit(1);
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

	CollisionNum = 0;
	CurrentPos = Hash(Key, H->TableSize);
	// There is no condition to stop infinite loop, because the default
	// TableSize is bigger than input elements in the test file.
	while (H->TheCells[CurrentPos].Info != Empty &&
		Compare(H->TheCells[CurrentPos].Element, Key) != EQUAL)
	{
		CurrentPos += 2 * ++CollisionNum - 1;
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

	Pos = Find(Key, H);
	if (H->TheCells[Pos].Info != Legitimate)
	{
		// OK to insert here
		H->TheCells[Pos].Info = Legitimate;
		H->TheCells[Pos].Element = Key;
		H->CurrentNum++;
	}
	if ((double)(H->CurrentNum) / (double)(H->TableSize) >= 0.7)
		H = Rehash(H);
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