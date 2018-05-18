// list.c -- functions supporting list operations
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"��ϰ3.1 list.h"

// local function prototype
static void CopyToNode(Item item, Node * pnode);

// interface functions
// set the list to empty
void InitializeList(List * plist)
{
	*plist = NULL;
}

// returns true is list is empty
bool ListIsEmpty(const List * plist)
{
	if (*plist == NULL)
		return true;
	else
		return false;
}

// returns true if list is full
bool ListIsFull(const List * plist)
{
	Node * pt;
	bool full;

	pt = (Node *)malloc(sizeof(Node));		// ����ڴ��Ѿ���ռ�������б��Ѿ��ﵽ��󣩣���ô��������ڴ�����ʧ�ܣ�ͨ�����ַ�����ʵ�� ListIsFull
	if (pt == NULL)
		full = true;
	else
		full = false;

	free(pt);

	return full;
}

// returns number of nodes
unsigned int ListItemCount(const List * plist)
{
	unsigned int count = 0;
	Node * pnode = *plist;		// set to start of list

	while (pnode!=NULL)
	{
		++count;
		pnode = pnode->next;	// set to next node
	}

	return count;
}

// creates node to hold item and adds it to the end of the list pointed to by plist (slow implementation)
bool AddItem(Item item, List * plist)		// �����ָ�봫����ֱ����ӵĻ����ͻ����һ����ӵĸ��ǵ�
{
	Node * pnew;
	Node * scan = *plist;

	pnew = (Node *)malloc(sizeof(Node));
	if (pnew == NULL)			// �ڴ����ʧ�ܣ���Ϊ�Ѿ���ռ��
		return false;			// quit function on failure

	CopyToNode(item, pnew);
	pnew->next = NULL;
	if (scan == NULL)			// empty list, so place pnew
		*plist = pnew;			// at head of list
	else
	{
		while (scan->next != NULL)
			scan = scan->next;	// find end of list
		scan->next = pnew;		// add pnew to end
	}

	return true;
}

// visit each node and execute function pointed to by pfun
void Traverse(const List * plist, void(*pfun)(Item item))
{
	Node * pnode = *plist;		// set to start of list

	puts("------------------------------------------------");
	while (pnode!=NULL)
	{
		(*pfun)(pnode->item);	// apply function to item
		pnode = pnode->next;	// advance to next item
	}
	puts("\n------------------------------------------------");
}

// free memory allocated by malloc()
// set list pointer to NULL
void EmptyTheList(List * plist)
{
	Node * psave;

	while (*plist !=NULL)
	{
		psave = (*plist)->next;	// save address of next node
		free(*plist);			// free current node
		*plist = psave;			// advance to next node
	}
}

// local function definition
// copies an item into a node
static void CopyToNode(Item item, Node * pnode)
{
	pnode->item = item;			// structure copy
}