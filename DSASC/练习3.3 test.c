/* compiles with
	Á·Ï°3.1 list.h
	Á·Ï°3.1 list.c
	../Library/s_and_r.c ³ÌÐò.h
*/

#include<stdio.h>
#include"Á·Ï°3.1 list.h"
#include"../Library/s_and_r.c ³ÌÐò.h"
#include<time.h>

#define MAX 10

void PrintItem(Item item);

Node * FindPrev(Node * node, List * plist);

// Exchange this and the successor node
void Exchange(Node * node, List * plist);

int main(void)
{
	List L;
	int index = 0;

	// arrange the list
	InitializeList(&L);
	srand1((unsigned)time(0));
	for (int i = 0; i < MAX; i++)
		AddItem(rand1(), &L);

	// select a node
	Node * testNode = L;
	while (index < 0)
	{
		index++;
		testNode = testNode->next;
	}

	// exchange
	puts("Before exchange:");
	Traverse(&L, PrintItem);
	Exchange(testNode, &L);
	puts("After exchange:");
	Traverse(&L, PrintItem);

	EmptyTheList(&L);
	return 0;
}

void
PrintItem(Item item)
{
	printf("%5d ", item);
}

Node * FindPrev(Node * node, List * plist)
{
	Node * prev = *plist;

	if (!ListIsEmpty(plist) && node != prev && node->next != NULL)
		while (prev->next != NULL)
		{
			if (prev->next == node)
				return prev;
			else
				prev = prev->next;
		}

	return NULL;
}

void Exchange(Node * node, List * plist)
{
	if (!ListIsEmpty(plist) && node->next != NULL)
	{
		Node * next = node->next;
		Node * prev = FindPrev(node, plist);
		
		if (prev!=NULL)
		{
			prev->next = next;
			node->next = next->next;
			prev->next->next = node;
		}
		else
		{
			node->next = next->next;
			next->next = node;
			*plist = next;
		}
	}
}
