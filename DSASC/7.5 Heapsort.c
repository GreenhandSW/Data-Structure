#include"7.5 Heapsort.h"
#include"../Library/General.h"

#define LeftChild(i) (2 * (i) + 1)

void PercolateDown(ElementType List[], int Pos, int Length)
{
	int Child;
	ElementType Tmp;

	for (Tmp = List[Pos]; LeftChild(Pos) < Length; Pos = Child)
	{
		Child = LeftChild(Pos);
		if (Child != Length - 1 && List[Child + 1] > List[Child])
			Child++;
		if (Tmp < List[Child])
			List[Pos] = List[Child];
		else
			break;
	}
	List[Pos] = Tmp;
}

void Heapsort(ElementType List[], int Length)
{
	for (int i = Length / 2; i >= 0; i--)	// Build heap
		PercolateDown(List, i, Length);
	for (int i = Length - 1; i > 0; i--)
	{
		Swap(&List[0], &List[i]);	// Delete max
		PercolateDown(List, 0, i);
	}
}