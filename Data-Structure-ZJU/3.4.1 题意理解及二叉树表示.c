#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include"3.4.1 BinaryTree(string version).h"

// find father of item[k]
int FindFather(BinaryTree * bt, int k);
int FindRoot(BinaryTree * bt);
bool Compare(BinaryTree * bt1, BinaryTree * bt2, int k1, int k2);

int main(void)
{
	BinaryTree bt1;
	BinaryTree bt2;
	int root1, root2;

	InitializeBinaryTree(&bt1);
	InitializeBinaryTree(&bt2);
	root1 = FindRoot(&bt1);
	root2 = FindRoot(&bt2);
	if (Compare(&bt1, &bt2, root1, root2))
		puts("They are the same!");
	else
		puts("They are different!");
	return 0;
}


int FindFather(BinaryTree * bt, int k)
{
	for (int i = 0; i < MAX; i++)
		if (k == (*bt).childs[0][i] || k == (*bt).childs[1][i])
			return i;	// father found

	return Null;			// father not found
}

int FindRoot(BinaryTree * bt)
{
	int father = 0;
	int root;
	while (father >= 0)
	{
		root = father;
		father = FindFather(bt, father);
	}

	return root;
}

bool Compare(BinaryTree * bt1, BinaryTree * bt2, int k1, int k2)
{
	if (k1 == Null && k2 == Null)						// if both k1 and k2 are Null, they are the same
		return true;
	else if (k1 == Null && k2 != Null)
		return false;
	else if (k1 != Null && k2 == Null)
		return false;
	if (strcmp((*bt1).item[k1], (*bt2).item[k2]))	// if their item are different, they are different
		return false;
	int left1, left2, right1, right2;

	left1 = (*bt1).childs[0][k1];
	right1 = (*bt1).childs[1][k1];
	left2 = (*bt2).childs[0][k2];
	right2 = (*bt2).childs[1][k2];

	if (!Compare(bt1, bt2, left1, left2) || !Compare(bt1, bt2, left1, left2))
	{
		if (Compare(bt1, bt2, left1, right2) && Compare(bt1, bt2, right1, left2))
			return true;
		else
			return false;
	}
	else
		return true;
}
