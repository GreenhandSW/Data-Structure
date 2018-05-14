#include<stdio.h>

typedef int ElementType;
typedef struct TreeNode * PtrToNode;
typedef PtrToNode Tree;

struct TreeNode
{
	ElementType Element;
	Tree Left;
	Tree Right;
};