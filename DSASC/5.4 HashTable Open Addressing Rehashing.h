#ifndef _HashTable_Open_Addressing_Rehashing_H

#define STRLEN 5
typedef char * ElementType;
typedef int Index;
typedef Index Position;

typedef struct HashTbl HashTbl;
typedef struct HashTbl * HashTable;

HashTable InitializeTable(int TableSize);
void DestroyTable(HashTable H);
void Delete(ElementType Key, HashTable H);
HashTable MakeEmpty(HashTable H);
Position Find(ElementType Key, HashTable H);
void Insert(ElementType Key, HashTable H);
ElementType Retrieve(Position P, HashTable H);
void Traverse(HashTable H, void(*pfun)(ElementType X));

#endif // !_HashTable_Open_Addressing_Quadratic_Probing_H
