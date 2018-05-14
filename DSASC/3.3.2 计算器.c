/* this file needs to be compiled with
	3.3.2 计算器.h
	3.3.2 栈的数组实现 Stack.h
	../Library/通用.h
	3.3.2 栈的数组实现 test.c
	3.3.2 栈的数组实现 implementation.c
*/

/* remaining problems:
	1. can't correctly handle with multiply minus of a number
	2. no fault-tolerant mechanism
	3. space processing is neither quitely good-looking nor convenient
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<stdbool.h>
#include<math.h>
#include"3.3.2 计算器.h"

const char * operators = "+-*/^()";

void
InsertSpace(int * sign, char ** dst, int * position)
{
	if (*sign && (*dst)[(*position) - 1] != ' ')
	{
		(*dst)[(*position)++] = ' ';
		(*sign)--;
	}
}

int
OperatorPosition(const char x)
{
	int lvl = strchr(operators, x) - operators;

	return lvl;
}

void
Infix2Postfix(const char * src, char * dst)
{
	Stack S = CreateStack(100);
	int j = 0;
	int sign = 0;
	//int tmp = 0;

	MakeEmpty(S);
	for (int i = 0; i < strlen(src)/*, j < strlen(dst)*/; i++)
	{
		if (isdigit(src[i]) || src[i] == '.')
		{
			//tmp = tmp * 10 + src[i] % 16;
			dst[j++] = src[i];
			sign++;
		}
		else if(src[i]!=' ')
		{
			InsertSpace(&sign, &dst, &j);
			if (OperatorPosition(src[i]) <= OperatorPosition('('))
			{
				while (!IsEmpty(S) && (OperatorPosition((char)Top(S)) / 2 >= OperatorPosition(src[i]) / 2) && src[i] != '(' && Top(S) != '(')
				{
					if ((char)Top(S)=='^' && (OperatorPosition((char)Top(S)) / 2 == OperatorPosition(src[i]) / 2))
						break;		// the "power" calculation doesn't associate right to left, so the loops ends if Top(S) is found equal to '^' and src[i]
					dst[j++] = (char)TopAndPop(S);
					InsertSpace(&sign, &dst, &j);
				}
				InsertSpace(&sign, &dst, &j);
				Push(src[i], S);
			}
			else
			{
				while (!IsEmpty(S) && Top(S) != '(')
				{
					dst[j++] = (char)TopAndPop(S);
					InsertSpace(&sign, &dst, &j);
				}
				InsertSpace(&sign, &dst, &j);
				if(!IsEmpty(S))
					Pop(S);
			}
		}
	}
	while (!IsEmpty(S))
	{
		dst[j++] = (char)TopAndPop(S);
		InsertSpace(&sign, &dst, &j);
	}
	if (dst[j - 1] == ' ')
		dst[j - 1] = '\0';
	else
		dst[j] = '\0';
	DisposeStack(S);
}

ElementType
Calc(const char * src)
{
	const FUNC operations[] = { plus, minus, multiply, divide ,pow };
	ElementType tmp = 0;		// temporary number for transforming numbers in a string to float numbers.
	Stack S = CreateStack(100);
	bool number_flag = false;	// if is number, turn this to true.
	bool dot_flag = false;		// if is decimal, turn this to true.
	int dot_count = 0;			// if is decimal, this counts the digits.
	ElementType outcome = 0;	// save the outcome of every step.

	MakeEmpty(S);
	for (int i = 0; i < strlen(src); i++)
	{
		if (isdigit(src[i]))
		{
			if (!dot_flag)
			{
				tmp = tmp * 10 + src[i] - 0x30;
				number_flag = true;
			}
			else
			{
				dot_count--;
				tmp = tmp + (src[i] - 0x30)*pow(10, dot_count);
			}
		}
		else if (src[i] == '.')
		{
			dot_flag = true;
		}
		else
		{
			if (number_flag == true)
				Push(tmp, S);
			number_flag = false;
			dot_flag = false;
			tmp = 0;
			dot_count = 0;
			int crnt_oprtr = -1;
			crnt_oprtr = OperatorPosition(src[i]);	// the position of the operator currently processing in the "operators" array
			if (crnt_oprtr >= 0 && crnt_oprtr <= 4)
			{
				ElementType x = 0;
				ElementType y = 0;
				if (!IsEmpty(S))
					x = TopAndPop(S);
				if (!IsEmpty(S))
					y = TopAndPop(S);
				outcome = operations[crnt_oprtr](y, x);
				Push(outcome, S);
			}

		}

	}
	DisposeStack(S);
	return outcome;
}

ElementType
plus(const ElementType x, const ElementType y)
{
	return x + y;
}

ElementType
minus(const ElementType x, const ElementType y)
{
	return x - y;
}

ElementType
multiply(const ElementType x, const ElementType y)
{
	return x * y;
}

ElementType
divide(const ElementType x, const ElementType y)
{
	return x / y;
}