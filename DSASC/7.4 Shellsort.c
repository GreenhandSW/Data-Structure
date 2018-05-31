#include"7.4 Shellsort.h"

void Shellsort(ElementType List[], int Length)
{
	ElementType Tmp;
	int j;

	for (int Increment = Length / 2; Increment > 0; Increment >>= 1)
	{
		for (int i = Increment; i < Length; i++)
		{
			Tmp = List[i];
			for (j = i; j >= Increment && List[j - Increment] > Tmp; j -= Increment)
				List[j] = List[j - Increment];
			List[j] = Tmp;
		}
	}
}