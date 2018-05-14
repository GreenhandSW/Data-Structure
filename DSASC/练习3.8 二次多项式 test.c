/* compiles with
	¡∑œ∞3.1 list.h
	¡∑œ∞3.1 list.c
	../Library/s_and_r.c ≥Ã–Ú.h
*/


#include<stdio.h>
#include"¡∑œ∞3.7 list.h"
#include"Õ®”√.h"
#include<math.h>

#define MAX 10

void PrintItem(Item item);
List Product(List * plist1, List * plist2);
// find node with the same exp
Node * ExpExist(const Item item, List * plist);
// multiply two node
Item Multiply(const Node * n1, const Node * n2);
// find the node with the greatest exp smaller than that of item 
Node * FindPre(const Item item, List * plist);
// calculate the exponential of polynomimal
List Poly_Emp(List * source, int exp);

int
main(void)
{
	int exp = 10;

	List L1;
	List polynominal_exponential;
	Item arr1[] = { {1,2},{2,3} };

	// arrange the list
	InitializeList(&L1);
	for (int i = 0; i < sizeof(arr1)/sizeof(Item); i++)
		AddItem(arr1[i], &L1);

	// union
	puts("List 1:");
	Traverse(&L1, PrintItem);

	polynominal_exponential = Poly_Emp(&L1, exp);
	printf("Exponential %d:\n", exp);
	Traverse(&polynominal_exponential, PrintItem);

	EmptyTheList(&L1);
	EmptyTheList(&polynominal_exponential);
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

	if (tmp == *plist|| tmp->item.exp>=item.exp)
		return *plist;
	else
		return tmp;
}

List Poly_Emp(List * source, int exp)
{
	List product;	// store the final output
	Item tmp;
	Item a = (*source)->item, b = (*source)->next->item;

	InitializeList(&product);
	
	for (int i = 0; i <= exp; i++)
	{
		tmp.coefficient = Combinatorial_Num(exp, i)*(int)pow(a.coefficient, exp - i)*(int)pow(b.coefficient, i);
		tmp.exp = a.exp*(exp - i) + b.exp*i;
		AddItem(tmp, &product);
	}

	return product;
}
