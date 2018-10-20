// Interface to BSTree
// Completed with code from COMP2521 week10 lab exercise
// Written by Steven Deng and Ying Zhong, October 2018

#ifndef BSTREE_H
#define BSTREE_H

typedef struct BSTNode *BSTree;

typedef struct SetNode *BSTSet;
// create an empty BSTree
BSTree newBSTree();
// free memory associated with BSTree
void dropBSTree(BSTree);
// display BSTree root node
void showBSTreeNode(BSTree, FILE *);

// print values in infix order
void BSTreeInfix(BSTree);
// print values in prefix order
void BSTreePrefix(BSTree);
// print values in postfix order
void BSTreePostfix(BSTree);

// count #nodes in BSTree
int BSTreeNumNodes(BSTree);
// count #leaves in BSTree
int BSTreeNumLeaves(BSTree);

// insert a new value into a BSTree
BSTree BSTreeInsert(BSTree, char *);
// check whether a value is in a BSTree
int BSTreeFind(BSTree, char *);
// delete a value from a BSTree
BSTree BSTreeDelete(BSTree, char *);

// Set operations
BSTSet insertNode (BSTSet, char *);
BSTSet deleteNode (BSTSet, char *);
void freeSet(BSTSet);

#endif
