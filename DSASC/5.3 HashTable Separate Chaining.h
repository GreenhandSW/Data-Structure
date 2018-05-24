#ifndef _HashTable_Separate_Chaining_H
#include<string.h>
#define STRLEN 5

typedef char * ElementType;
typedef struct ListNode ListNode;
typedef ListNode * Position;
typedef struct HashTbl HashTbl;
typedef HashTbl * HashTable;
typedef Position List;

HashTable InitializeTable(int TableSize);
// I guess this process makes the Table completely empty,
// because if I want to make the Table completely empty,
// it must return NULL, as for 'DestroyTable' doesn't
// return anything, this process is the only choice.
HashTable MakeEmpty(HashTable H);
// I guess this process makes the Lists empty
void DestroyTable(HashTable H);
Position Find(ElementType Key, HashTable H);
void Delete(ElementType Key, HashTable H);
void Insert(ElementType Key, HashTable H);
ElementType Retrieve(Position P);
void Traverse(HashTable H, void(*pfun)(ElementType X));
int GetSize(HashTable H);
// get the number of elements in the table
int GetCurrentCount(HashTable H);
#endif // !_HashTable_Separate_Chaining_H
