#include<stdio.h>
#include<time.h>
#include"../Library/s_and_r.h"
#include"../Library/General.h"
#include"5.3 HashTable Separate Chaining.h"

#define MAXLENGTH 100

void PrintElement(ElementType X);

int main(void)
{
	HashTable H;
	char list[MAXLENGTH][STRLEN];
	//int random;
	int count = MAXLENGTH - 1;

	H = InitializeTable(8);
	// Generate a random array
	for (int i = 0; i < MAXLENGTH; i++)
	{
		//srand1((unsigned)time(0)*(i + 1));
		GenerateRandomString(list[i], STRLEN);
		printf("%s ", list[i]);
	}
	puts("");
	// Insert elements of array to HashTable
	for (int i = 0; i < MAXLENGTH; i++)
	{
		Insert(list[MAXLENGTH - i - 1], H);
		puts("---------------------------");
		printf("After Insert %s: ", list[i]);
		Traverse(H, PrintElement);
		puts("");
	}

	int i = 0;
	while (GetCurrentCount(H))
	{
		char * found = Retrieve(Find(list[i], H));
		Delete(found, H);
		puts("---------------------------");
		printf("After Delete %s: ", found);
		Traverse(H, PrintElement);
		puts("");
		i++;
	}

	H = MakeEmpty(H);
	return 0;
}

void PrintElement(ElementType X)
{
	if (X)
		printf("%s ", X);
}