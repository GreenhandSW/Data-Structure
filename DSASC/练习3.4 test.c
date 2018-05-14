/* compiles with
	¡∑œ∞3.1 list.h
	¡∑œ∞3.1 list.c
	D:\Programming\CPP\≥Ã–Ú«Âµ•12.9 s_and_r.c ≥Ã–Ú.c
*/

#include<stdio.h>
#include"¡∑œ∞3.1 list.h"

#define MAX 10

void PrintItem(Item item);
List Intersection(const List * plist1, const List * plist2);

int
main(void)
{
	List L1,L2;
	List disjoint;
	int arr1[] = { 1,2,4,5,8,12,14,17,20,22,27,29,39,41,42,43,44 };
	int arr2[] = { 2,4,8,12,13,16,17,20,25,27,33,39,44 };

	// arrange the list
	InitializeList(&L1);
	InitializeList(&L2);

	for (int i = 0; i < sizeof(arr1)/sizeof(int); i++)
		AddItem(arr1[i], &L1);
	for (int i = 0; i < sizeof(arr2)/sizeof(int); i++)
		AddItem(arr2[i], &L2);

	// disjoint
	puts("List 1:");
	Traverse(&L1, PrintItem);
	puts("List 2:");
	Traverse(&L2, PrintItem);

	disjoint = Intersection(&L1, &L2);
	puts("Intersection:");
	Traverse(&disjoint, PrintItem);

	EmptyTheList(&L1);
	EmptyTheList(&L2);
	EmptyTheList(&disjoint);
	return 0;
}

void
PrintItem(Item item)
{
	printf("%5d ", item);
}

List Intersection(const List * plist1, const List * plist2)
{
	List disjoint;
	InitializeList(&disjoint);
	Node * n1 = *plist1;
	Node * n2 = *plist2;

	if(!ListIsEmpty(plist1) || !(ListIsEmpty(plist2)))
	{
		while (n1 != NULL && n2 != NULL)
		{
			if (n1->item < n2->item)
				n1 = n1->next;
			else if (n1->item > n2->item)
				n2 = n2->next;
			else
			{
				AddItem(n1->item, &disjoint);
				n1 = n1->next;
				n2 = n2->next;
			}
		}
	}

	return disjoint;
}
