#include<stdio.h>
#include<math.h>
#include "General.h"

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

void Swap(int * a, int * b)
{
	int tmp = *a;
	*a=*b;
	*b=tmp;
}

int NextPrime(int n)
{
	int prime = n - 1;	// make prime smaller than n
	int x = n + 1;		// search from next number of n
	int abs_value;		// store absolute value of x
	while (prime < n)
	{
		abs_value = abs(x);
		int i;
		for (i = 2; i*i < abs_value; i++)
			if (x%i == 0)	// x can be fully divided by i, so it's not a prime
				break;
		// i*i>abs_value means that |x| can't be divided by i that's smaller than |x|^0.5
		// and abs_value>1 means if |x| is 0 or 1, it's not a prime
		if (i*i > abs_value && abs_value > 1)
			prime = x;
		else
			x++;		// try next value
	}

	return prime;
}

int PrevPrime(int n)
{
	int prime = n + 1;	// make prime bigger than n
	int x = n - 1;		// search from next number of n
	int abs_value;		// store absolute value of x
	while (prime > n)
	{
		abs_value = abs(x);
		int i;
		for (i = 2; i*i < abs_value; i++)
			if (x%i == 0)	// x can be fully divided by i, so it's not a prime
				break;
		// i*i>abs_value means that |x| can't be divided by i that's smaller than |x|^0.5
		// and abs_value>1 means if |x| is 0 or 1, it's not a prime
		if (i*i > abs_value && abs_value > 1)
			prime = x;
		else
			x--;		// try last value
	}

	return prime;
}

int Log2Ceiling(int n)
{
	int value;

	if (n <= 0)
		value = -2147483647;
	else
	{
		value = (int)log2(n);
		if (1 << ((int)value) < n)
			value++;
	}

	return value;
}
