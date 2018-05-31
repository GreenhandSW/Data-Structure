#include "7.2 Insertion Sort.h"

void InsertionSort(ElementType List[], int Length)
{
	ElementType Tmp;
	int j;

	for (int i = 1; i < Length; i++)
	{
		Tmp = List[i];
		for (j = i; j > 0 && List[j - 1] > Tmp; j--)
			List[j] = List[j - 1];
		List[j] = Tmp;
	}
}