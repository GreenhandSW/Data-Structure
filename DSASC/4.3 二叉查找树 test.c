#pragma once
/* Compiles with
	4.3 ���������.h
	4.3 ���������.c
	../Library/s_and_r.h
	../Library/s_and_r.c
	../Library/ͨ��.h
	../Library/ͨ��.c
	*/
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include"4.3 ���������.h"
#include"../Library/s_and_r.h"
#include"../Library/ͨ��.h"
#define MAX 20

void PrintElement(ElementType X);
int Random(int min, int max);

int main(void)
{
	TreeHeadPtr THP;
	int list[MAX];
	int random;
	int count = MAX-1;

	THP = MakeTreeEmpty(NULL);
	for (int i = 0; i < MAX; i++)
	{
		srand1((unsigned)time(0)*(i+1));
		list[i] = Random(0, 100);
		printf("%d ", list[i]);
	}
	puts("");
	for (int i = 0; i < MAX; i++)
	{
		Insert(list[i], THP);
		printf("After Insert %2d: ", list[i]);
		InOrder(PrintElement, THP);
		puts("");
	}
	int size = GetSearchTreeSize(THP);
	while ( size> 0)
	{
		random = Random(0, count+1);
		Delete(list[random], THP);
		int deleted = list[random];

		Swap(&(list[random]), &(list[count]));
		count--;
		printf("After Delete %2d: ", deleted);
		InOrder(PrintElement, THP);
		puts("");
		size = GetSearchTreeSize(THP);
	}

	MakeTreeEmpty(THP);
	free(THP);
	return 0;
}

void PrintElement(ElementType X)
{
	printf("%2d ", X);
}

int Random(int min, int max)
{
	return rand1() % (max - min) + min;
}