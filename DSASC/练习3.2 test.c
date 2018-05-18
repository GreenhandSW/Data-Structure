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
typedef double TIMETYPE;	// to conveniently change the type of the value of time

void PrintItem(Item item);
void PrintLots(List * L, List * P);

void
PrintItem(Item item)
{
	printf("%5d ", item);
}

void
PrintLots(List * L, List * P)
{
	int index = 0;
	Node * L_Traverse = (*L);
	Node * P_Traverse = (*P);
	while (L_Traverse != NULL && P_Traverse != NULL)
	{
		if (index == P_Traverse->item)
		{
			PrintItem(L_Traverse->item);
			P_Traverse = P_Traverse->next;
		}
		else
			printf("      ");
		L_Traverse = L_Traverse->next;
		index++;
	}
	puts("");
}

int main(void)
{
	List L, P;
	int indices[] = { 1,4,6,7,9 };

	InitializeList(&L);
	InitializeList(&P);
	srand1((unsigned)time(0));
	for (int i = 0; i < MAX; i++)
		AddItem(rand1(), &L);
	for (int i = 0; i < 5; i++)
		AddItem(indices[i], &P);

	Traverse(&L, PrintItem);
	Traverse(&P, PrintItem);

	TIMETYPE start = (TIMETYPE)clock();
	PrintLots(&L, &P);
	TIMETYPE end = (TIMETYPE)clock();
	printf("The PrintLots costs %lf ms", end - start);

	EmptyTheList(&L);
	EmptyTheList(&P);

	return 0;
}