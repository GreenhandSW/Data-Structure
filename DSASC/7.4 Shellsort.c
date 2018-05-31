#include"7.4 Shellsort.h"
#include"../Library/General.h"

#define SedgewickLen 28
#define Compare(X, Y) (((X) > (Y)) ? (BIGGER) : (((X) == (Y)) ? (EQUAL) : (SMALLER)))
typedef int Position;

// Directly generated a Sedegwick increment sequence, since there are 
// only these numbers in the sequence within the range of int
ElementType SedgewickIncrement[] = { 1, 5, 19, 41, 109, 209, 505, 929, 2161, 3905, 8929, 16001,
							36289, 64769, 146305, 260609, 587521, 1045505, 2354689, 
							4188161, 9427969, 16764929, 37730305, 67084289, 150958081, 
							268386305, 603906049, 1073643521 };
Position IndexOfMaxSmaller(ElementType X, ElementType List[], int Length);

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

void ShellsortHibbard(ElementType List[], int Length)
{
	ElementType Tmp;
	int j;

	for (int Increment = (1 << Log2Ceiling(Length)) - 1; Increment > 0; Increment >>= 1)
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

void ShellsortSedegwick(ElementType List[], int Length)
{
	ElementType Tmp, Increment;
	int j;
	Position SedgewickIndex;

	SedgewickIndex = IndexOfMaxSmaller(Length, SedgewickIncrement, SedgewickLen);
	if (SedgewickIndex >= 0)
	{
		for (; SedgewickIndex >= 0; SedgewickIndex--)
		{
			Increment = SedgewickIncrement[SedgewickIndex];
			for (int i = Increment; i < Length; i++)
			{
				Tmp = List[i];
				for (j = i; j >= Increment && List[j - Increment] > Tmp; j -= Increment)
					List[j] = List[j - Increment];
				List[j] = Tmp;
			}
		}
	}
}

Position IndexOfMaxSmaller(ElementType X, ElementType List[], int Length)
{
	int min, max, mid;
	int result;

	min = 0;
	max = Length - 1;
	while (min < max)
	{
		mid = (min + max) >> 1;
		result = Compare(X, List[mid]);
		if (result == BIGGER)
			min = mid + 1;
		else if (result == EQUAL)
			return mid - 1;
		else	// result == SMALLER
			max = mid - 1;
	}
	if (X > List[min])
		return min;
	else
		return min - 1;
}