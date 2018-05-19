/* compiles with
	��ϰ3.1 list.h
	��ϰ3.1 list.c
	../Library/s_and_r.h
	../Library/s_and_r.c
*/


#include<stdio.h>
#include"��ϰ3.7 list.h"

#define MAX 10
#define MAXCOEF 10000-1	// the biggest coefficient

void PrintItem(Item item);
List Product(List * plist1, List * plist2);
// find node with the same exp
Node * ExpExist(const Item item, List * plist);
// multiply two node
Item Multiply(const Node * n1, const Node * n2);
// find the node with the greatest exp smaller than that of item 
Node * FindPre(const Item item, List * plist);
// recursively reduce the exponential
List Poly_Emp(List * source, int * reduced_list, int minExp_index);
int Reduce_Exp(int exp, int * reduced_list);
// for digital number: if a digit>9 carry the high-digit to the higher digit
void Correct_Carry(List * source);

int
main(void)
{
	int exp = 1000;
	int reduced_list[50];

	int minExp_index = Reduce_Exp(exp, reduced_list);
	for (int i = minExp_index; i >= 0; i-- )
		printf("%d ", reduced_list[i]);

	List L1;
	List polynominal_exponential;
	Item arr1[] = { {2,0}/*,{2,3},{8,12},{7,8},{14,17},{20,22},{27,29},{39,41},{42,43},{44,47}*/ };

	// arrange the list
	InitializeList(&L1);
	for (int i = 0; i < sizeof(arr1)/sizeof(Item); i++)
		AddItem(arr1[i], &L1);

	// union
	puts("List 1:");
	Traverse(&L1, PrintItem);

	polynominal_exponential = Poly_Emp(&L1, reduced_list, minExp_index);
	printf("Exponential %d:", exp);
	Traverse(&polynominal_exponential, PrintItem);

	EmptyTheList(&L1);
	EmptyTheList(&polynominal_exponential);
	return 0;
}

void
PrintItem(Item item)
{
	printf("%d", item.coefficient);
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

List Poly_Emp(List * source, int * reduced_list, int minExp_index)
{
	int i = minExp_index - 1;
	List product;	// store the final output
	List assist;	// store assistant output
	List tmp;		// for temporary use
	InitializeList(&product);
	InitializeList(&assist);
	InitializeList(&tmp);
	product = *source;
	assist = *source;

	while(i>=0)
	{
		if (reduced_list[i] == reduced_list[i + 1] + 1)
		{
			assist = product;
			tmp = Product(&product, source);
			product = tmp;
		}
		else
		{
			if (reduced_list[i] % 2 == 0)
			{
				tmp = Product(&product, &product);
				product = tmp;
			}
			else
			{
				tmp = Product(&product, &assist);
				product = tmp;
			}
		}
		i--;
		Correct_Carry(&product);
	}

	EmptyTheList(&assist);
	return product;
}


int Reduce_Exp(int exp, int * reduced_list)
{
	int min_index = 0;	// the index of the minimum number
	while (exp > 1)
	{
		reduced_list[min_index] = exp;
		if (exp % 2 != 0)
		{
			reduced_list[++min_index] = (exp + 1) / 2;
			reduced_list[++min_index] = exp / 2;
			exp /= 2;
		}
		else
		{
			reduced_list[++min_index] = exp / 2;
			exp /= 2;
		}
	}

	return min_index;
}

void Correct_Carry(List * source)
{
	Node * traverse = *source;
	
	while (traverse!=NULL)
	{
		if (traverse->item.coefficient >= 32768 && (traverse==*source))
		{
			Item tmp;

			tmp.exp = (*source)->item.exp + 9;
			InsertItem(tmp, source, source);
			(*source)->next->item.coefficient = (*source)->item.coefficient % (MAXCOEF + 1);
			(*source)->item.coefficient = (*source)->item.coefficient / (MAXCOEF + 1);
			//traverse = *source;
			//traverse->item.coefficient += traverse->item.coefficient / (MAXCOEF + 1);
			//traverse->next->item.coefficient = traverse->next->item.coefficient % (MAXCOEF + 1);
		}
		traverse = traverse->next;
	}
}
