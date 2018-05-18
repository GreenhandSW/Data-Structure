#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include"3.4.1(2) BinaryTree(string version).h"

int InitializeBinaryTree(BinaryTree * bt)
{
	int size;
	char item[STRINGLEN], left[STRINGLEN], right[STRINGLEN];
	int check[MAX];
	int i;
	
	scanf("%d", &size);
	if (size > MAX)
	{
		puts("error: tree size overflow!");
		exit(0);
	}
	for (i = 0; i < size; i++)
		check[i] = 0;
	for (i = 0; i < size; i++)
	{
		scanf("%s %s %s", item, left, right);
		strcpy((*bt).item[i], item);
		if (!strcmp(left, "-"))
			(*bt).childs[0][i] = Null;
		else
		{
			(*bt).childs[0][i] = atoi(left);
			check[(*bt).childs[0][i]] = 1;
		}
		if (!strcmp(right, "-"))
			(*bt).childs[1][i] = Null;
		else
		{
			(*bt).childs[1][i] = atoi(right);
			check[(*bt).childs[1][i]] = 1;
		}
	}
	for (i = 0; i < size; i++)
		if (check[i] == 0)
			break;

	return i;
}

bool InTree(Item * item, const BinaryTree * bt)
{
	for (int i = 0; i < MAX; i++)
		if (!strcmp(item, (*bt).item[i]))
			return true;

	return false;
}

void Traverse(const BinaryTree * bt, int k)
{
	if (k >= 0)
		Traverse(bt, (*bt).childs[0][k]);
	if (k >= 0)
		Traverse(bt, (*bt).childs[1][k]);
}