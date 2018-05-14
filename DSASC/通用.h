#include<stdio.h>

void FatalError(char * information)
{
	printf(information);
}

void Error(char * information)
{
	printf(information);
}

int Factorial(int n)
{
	int fact = 1;
	for (int i = 1; i <= n; i++)
	{
		fact *= n;
	}

	return fact;
}

// seems "Factorial" will be useless if i assign "n" to this "m"
int Reverse_Factorial(int n, int m)
{
	int fact = 1;
	for (int i = n; i > n - m; i--)
		fact *= n;

	return fact;
}

int Combinatorial_Num(int n, int m)
{
	int combinatorial;

	if (m > n / 2)
		m = n - m;

	combinatorial = Reverse_Factorial(n, m) / Reverse_Factorial(m, m);

	return combinatorial;
}