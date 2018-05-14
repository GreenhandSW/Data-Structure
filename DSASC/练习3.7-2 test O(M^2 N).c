/* compiles with
	¡∑œ∞3.1 list.h
	¡∑œ∞3.1 list.c
	../../../CPP/≥Ã–Ú«Âµ•12.9 s_and_r.c ≥Ã–Ú.c
*/

#include<stdio.h>
#include"¡∑œ∞3.6 list.h"

#define MAX 10

void PrintItem(Item item);
List Product(const List * plist1, const List * plist2);
Node * ExpExist(const Item item, const List * plist);
Item Multiply(const Node * n1, const Node * n2);

int
main(void)
{
	List L1,L2;
	List product;
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

	product = Product(&L1, &L2);
	puts("Product:");
	Traverse(&product, PrintItem);

	EmptyTheList(&L1);
	EmptyTheList(&L2);
	EmptyTheList(&product);
	return 0;
}

void
PrintItem(Item item)
{
	printf("%d^%d + ", item.coefficient, item.exp);
}

List Product(const List * plist1, const List * plist2)
{
	List product;
	InitializeList(&product);
	Node * n1 = *plist1;

	if (!ListIsEmpty(plist1) || !(ListIsEmpty(plist2)))
	{
		while (n1 != NULL)
		{
			Node * n2 = *plist2;
			while (n2!=NULL)
			{
				Item tmp = Multiply(n1, n2);
					Node * find = ExpExist(tmp, &product);
				if (find != NULL)
					find->item.coefficient += tmp.coefficient;
				else
					AddItem(tmp, &product);
				n2 = n2->next;
			}
			n1 = n1->next;
		}
	}

	return product;
}

Node * ExpExist(const Item item, const List * plist)
{
	Node * tmp = *plist;
	if (!ListIsEmpty(plist))
		while ((tmp != NULL) && (tmp->item.exp != item.exp))
			tmp = tmp->next;

	return tmp;
}

Item Multiply(const Node * n1, const Node * n2)
{
	Item multiplication;

	multiplication.coefficient = n1->item.coefficient * n2->item.coefficient;
	multiplication.exp = n1->item.exp + n2->item.exp;

	return multiplication;
}
