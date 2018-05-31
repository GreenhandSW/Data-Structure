#include<stdio.h>
#include<stdlib.h>
#include"7.6 Mergesort.h"
#include"../Library/General.h"

#define Compare(X, Y) (((X) > (Y)) ? (BIGGER) : (((X) == (Y)) ? (EQUAL) : (SMALLER)))

void
Merge(ElementType List[], ElementType TmpArray[], 
	int LeftPos, int RightPos, int RightEnd)
{
	int LeftEnd, TmpPos;
	int NumElements;

	LeftEnd = RightPos - 1;
	TmpPos = LeftPos;
	NumElements = RightEnd - LeftPos + 1;
	while (LeftPos <= LeftEnd && RightPos <= RightEnd)
	{
		if (Compare(List[LeftPos], List[RightPos]) != BIGGER)
			TmpArray[TmpPos++] = List[LeftPos++];
		else
			TmpArray[TmpPos++] = List[RightPos++];
	}

	while (LeftPos <= LeftEnd)	// Copy rest of first half
		TmpArray[TmpPos++] = List[LeftPos++];
	while (RightPos <= RightEnd)	// Copy rest of second half
		TmpArray[TmpPos++] = List[RightPos++];

	// Copy TmpArray back
	for (int i = 0; i < NumElements; i++, RightEnd--)
		List[RightEnd] = TmpArray[RightEnd];
}
void
SubMergesort(ElementType List[], ElementType TmpArray[], int Left, int Right)
{
	int Center;

	if (Left < Right)
	{
		Center = (Left + Right) >> 1;
		SubMergesort(List, TmpArray, Left, Center);
		SubMergesort(List, TmpArray, Center + 1, Right);
		Merge(List, TmpArray, Left, Center + 1, Right);
	}
}

void
Mergesort(ElementType List[], int Length)
{
	ElementType * TmpArray;

	TmpArray = malloc(sizeof(ElementType) * Length);
	if (TmpArray == NULL)
		FatalError("No space for temporary array!!!\n");
	else
	{
		SubMergesort(List, TmpArray, 0, Length - 1);
		free(TmpArray);
	}
}