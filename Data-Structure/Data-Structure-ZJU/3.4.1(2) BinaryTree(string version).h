#ifndef _BINARY_TREE_H_
#define _BINARY_TREE_H_
#include<stdbool.h>

#define MAX 10
#define STRINGLEN 10
#define Null -1
typedef char Item;		// the ElementType that binary tree stores
typedef struct {
	Item item[MAX][STRINGLEN];
	int childs[2][MAX];	// child[0][i] is the left child of item[i]
						// child[1][i] is the right child of item[i]
}BinaryTree;

// function prototypes

// operation:		initialize a binary tree to empty
// precondition:	bt points to a binary tree
// postconditions:	the binary tree is initialized
int InitializeBinaryTree(BinaryTree * bt);

//// operation:		add an item to a binary tree
//// preconditions:	pi is address of item to be added,
////					bt points to an initialized binary tree
//// postconditions:	if possible, function adds item to binary tree and returns
////					true; otherwise, the function returns false
//bool AddItem(const Item * pi, BinaryTree * bt);

// operation:		find an item in a binary tree
// preconditions:	pi points to an item,
//					bt points to an initialized binary tree
// postconditions:	function returns true if item is in binary tree
//					and returns false otherwise
bool InTree(Item * item, const BinaryTree * bt);

// operation:		delete an item from a binary tree
// preconditions:	pi is address of item to be deleted
//					bt points to an initialized binary tree
// postconditions:	if possible, function deletes item from binary tree
//					and returns true;
//					otherwise, the function returns false
//bool DeleteItem(const Item * pi, BinaryTree * bt);

// operation:		apply a function to each item in the binary tree
// preconditions:	bt points to a binary tree
//					pfun points to a function that takes an Item argument
//					and has no return value
// postconditions:	the function pointed to by pfun is executed once
//					for each item in binary tree
void Traverse(const BinaryTree * bt, int k);

// operation:		delete everything from a binary tree
// preconditions:	bt points to an initialized binary tree
// postconditions:	binary tree is empty
//void DeleteAll(BinaryTree * bt);
#endif // !_BINARY_TREE_H_