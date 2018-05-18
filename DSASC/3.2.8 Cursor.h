#pragma once
#ifndef _Cursor_H
typedef char ElementType;
typedef int PtrToNode;
typedef PtrToNode List;
typedef PtrToNode Position;

void InitializeCursorSpace(void);

List MakeEmpty(List L);
int IsEmpty(const List L);
int IsLast(const Position P, const List L);
Position Find(ElementType X, List L);
void Insert(ElementType X, List L, Position P);
void DeleteList(List L);
Position Header(const List L);
Position First(const Position L);
ElementType Retrieve(const Position P);

#endif // !_Cursor_H

#define SpaceSize 100
/* Place in the implementation file */
struct Node
{
	ElementType Element;
	Position Next;
};

struct Node CursorSpace[SpaceSize];