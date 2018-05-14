#pragma once
#include<stdio.h>
#include"4.3 二叉查找树.h"
#include"../Library/s_and_r.h"
#include"../Library/通用.h"
#define MAX 20

void PrintElement(ElementType X);

int main(void)
{
	SearchTree T;
	int list[MAX];
	int random;

	T = MakeEmpty(NULL);
	for (int i = 0; i < MAX; i++)
		list[i] = Random(0, 100);
	for (int i = 0; i < MAX; i++)
	{
		Insert(list[i], &T);
		InOrder(T, PrintElement);
	}
	for (int i = 0; i < MAX; i++)
	{
		random = Random(0, MAX - i);
		Delete(list[i], T);
		Swap(&(list[random]), &(list[MAX - 1]));
		InOrder(T, PrintElement);
	}

	MakeEmpty(T);
	return 0;
}

void PrintElement(ElementType X)
{
	printf("%d ", X);
}
