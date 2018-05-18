/* compiles with
	Á·Ï°3.1 list.h
	Á·Ï°3.1 list.c
	../Library/s_and_r.c ³ÌÐò.h
*/


#include<stdio.h>
#include"Á·Ï°3.7 list.h"

#define MAX 10

void PrintItem(Item item);
List Product(List * plist1, List * plist2);
// find node with the same exp
Node * ExpExist(const Item item, List * plist);
// multiply two node
Item Multiply(const Node * n1, const Node * n2);
// find the node with the greatest exp smaller than that of item 
Node * FindPre(const Item item, List * plist);

int
main(void)
{
	List L1,L2;
	List product;
	Item arr1[] = { {1,2},{4,5},{8,12},{7,8},{14,17},{20,22},{27,29},{39,41},{42,43},{44,47} };
	Item arr2[] = { {2,4},{6,5},{7,13},{17,20},{18,22},{33,39},{44,41},{5,3},{1,47} };

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
	printf("%dx^%d + ", item.coefficient, item.exp);
}

List Product(List * plist1, List * plist2)
{
	List product;
	InitializeList(&product);
	Node * n1 = *plist1;

	if (!ListIsEmpty(plist1) || !(ListIsEmpty(plist2)))
	{
		while (n1 != NULL)
		{
			Node * n2 = *plist2;
			while (n2 != NULL)
			{
				Item tmp = Multiply(n1, n2);
				Node * find = ExpExist(tmp, &product);
				if (find != NULL)
					// found a node with the same exp
					find->item.coefficient += tmp.coefficient;
				else
				{	// didn't find node with the same exp,
					// so find the greatest exp smaller than it,
					// then insert a node after the node of this exp
					Node * found = FindPre(tmp, &product);
					InsertItem(tmp, &found, &product);
					puts("");
				}
				n2 = n2->next;
			}
			n1 = n1->next;
		}
	}

	return product;
}

Node * ExpExist(const Item item, List * plist)
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

Node * FindPre(const Item item, List * plist)
{
	Node * tmp = *plist;
	if (!ListIsEmpty(plist))
		while ((tmp != NULL) && (tmp->next != NULL) && /*(tmp->item.exp < item.exp)&&*/(tmp->next->item.exp < item.exp))
			tmp = tmp->next;

	if (tmp == *plist|| tmp->item.exp>item.exp)
		return *plist;
	else
		return tmp;
}
