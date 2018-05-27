#include<stdio.h>

#define BIGGER 1
#define EQUAL 0
#define SMALLER -1
#define LEFT 0
#define RIGHT 1

void FatalError(char * information);
void Error(char * information);
// seems "Factorial" will be useless if i assign "n" to this "m"
int Reverse_Factorial(int n, int m);
int Combinatorial_Num(int n, int m);
void Swap(int * a, int * b);
// find the smallest prime bigger than n
int NextPrime(int n);
// find the biggest prime smaller than n
int PrevPrime(int n);