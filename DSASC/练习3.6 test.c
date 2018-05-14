/* compiles with
	¡∑œ∞3.1 list.h
	¡∑œ∞3.1 list.c
	D:\Programming\CPP\≥Ã–Ú«Âµ•12.9 s_and_r.c ≥Ã–Ú.c
*/

#include<stdio.h>
#include"¡∑œ∞3.6 list.h"

#define MAX 10

void PrintItem(Item item);
List Union(const List * plist1, const List * plist2);

int
main(void)
{
	List L1,L2;
	List union_my;
	Item arr1[] = { {1,2},{4,5},{8,12},{14,17},{20,22},{27,29},{39,41},{42,43},{44,47} };
	Item arr2[] = { {2,4},{6,5},{7,13},{17,20},{18,22},{33,39},{44,41},{1,47} };

	// arrange the list
	InitializeList(&L1);
	InitializeList(&L2);

	for (int i = 0; i < sizeof(arr1)/sizeof(Item); i++)
		AddItem(arr1[i], &L1);
	for (int i = 0; i < sizeof(arr2)/sizeof(Item); i++)
		AddItem(arr2[i], &L2);

	// union
	puts("List 1:");
	Traverse(&L1, PrintItem);
	puts("List 2:");
	Traverse(&L2, PrintItem);

	union_my = Union(&L1, &L2);
	puts("Union:");
	Traverse(&union_my, PrintItem);

	EmptyTheList(&L1);
	EmptyTheList(&L2);
	EmptyTheList(&union_my);
	return 0;
}

void
PrintItem(Item item)
{
	printf("%d^%d + ", item.coefficient, item.exp);
}

List Union(const List * plist1, const List * plist2)
{
	List union_my;
	InitializeList(&union_my);
	Node * n1 = *plist1;
	Node * n2 = *plist2;

	if (!ListIsEmpty(plist1) || !(ListIsEmpty(plist2)))
	{
		while (n1 != NULL && n2 != NULL)
		{
			if (n1->item.exp < n2->item.exp)
			{
				AddItem(n1->item, &union_my);
				n1 = n1->next;
			}
			else if (n1->item.exp > n2->item.exp)
			{
				AddItem(n2->item, &union_my);
				n2 = n2->next;
			}
			else
			{
				Item tmp;

				tmp.coefficient = n1->item.coefficient + n2->item.coefficient;
				tmp.exp = n1->item.exp;
				AddItem(tmp, &union_my);
				n1 = n1->next;
				n2 = n2->next;
			}
		}
		while (n1 != NULL)
		{
			AddItem(n1->item, &union_my);
			n1 = n1->next;
		}
		while (n2 != NULL)
		{
			AddItem(n2->item, &union_my);
			n2 = n2->next;
		}
	}

	return union_my;
}
