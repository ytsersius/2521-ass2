// Implementation of binary search tree ADT
// Completed with code from COMP2521 week10 lab exercise
// Written by Steven Deng and Ying Zhong, October 2018

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "BSTree.h"

typedef struct BSTNode *BSTLink;

typedef struct BSTNode {
	char *key;
	BSTSet urlSet;

	BSTLink left;
	BSTLink right;
} BSTNode;

typedef struct SetNode {
   char        *url;
   struct Node *next;
} SetNode;

// make a new node containing a value
static BSTLink newBSTNode(char *word)
{
	BSTLink new = malloc(sizeof(BSTNode));
	assert(new != NULL);
	new->key = strcpy(new->key, word);
	new->urlSet = NULL;
	new->left = new->right = NULL;
	return new;
}

// create a new empty BSTree
BSTree newBSTree()
{
	return NULL;
}

// free memory associated with BSTree
void dropBSTree(BSTree t)
{
	if (t == NULL) return;
	dropBSTree(t->left);
	dropBSTree(t->right);
	free(t);
}

// display BSTree root node
void showBSTreeNode(BSTree t, FILE *stream)
{
	if (t == NULL) return;
	fprintf(stream, "%s  ", t->key);

	SetNode *curr = t->urlSet;
	while (curr != NULL) {
		fprintf(stream, "%s ", curr->url);
		curr = curr->next;
	}

	fprintf(stream, "\n");
}

// print values in infix order
void BSTreeInfix(BSTree t, FILE *stream)
{
	if (t == NULL) return;
	BSTreeInfix(t->left, stream);
	showBSTreeNode(t, stream);
	BSTreeInfix(t->right, stream);
}

// print values in prefix order
void BSTreePrefix(BSTree t, FILE *stream)
{
	if (t == NULL) return;
	showBSTreeNode(t, stream);
	BSTreePrefix(t->left, stream);
	BSTreePrefix(t->right, stream);
}

// print values in postfix order
void BSTreePostfix(BSTree t, FILE *stream)
{
	if (t == NULL) return;
	BSTreePostfix(t->left, stream);
	BSTreePostfix(t->right, stream);
	showBSTreeNode(t, stream);
}

// count #nodes in BSTree
int BSTreeNumNodes(BSTree t)
{
	if (t == NULL)
		return 0;
	else
		return 1 + BSTreeNumNodes(t->left)
	             + BSTreeNumNodes(t->right);
}

// count #leaves in BSTree
int BSTreeNumLeaves(BSTree t)
{
	if (t == NULL) {
		return 0;
	} else {
		return 1 + BSTreeNumLeaves(t->left) + BSTreeNumLeaves(t->right);
	}
}

// insert a new value into a BSTree
BSTree BSTreeInsert(BSTree t, char *word)
{
	if (t == NULL)
		return newBSTNode(word);
	else if (strcmp(word, t->key) < 0)
		t->left = BSTreeInsert(t->left, word);
	else if (strcmp(word, t->key) > 0)
		t->right = BSTreeInsert(t->right, word);
	else
		/* don't insert duplicates */;
	return t;
}

// find a value in a BSTree and return the node
BSTNode *BSTreeFind(BSTree t, char *word)
{
	if (t == NULL)
		return 0;

	else if (strcmp(word, t->key) < 0)
		return BSTreeFind(t->left, word);

	else if (strcmp(word, t->key) > 0)
		return BSTreeFind(t->right, word);

	else // (v == t->value)
		return t;
}

// delete root of tree
static
BSTree deleteRoot(BSTree t)
{
	// if no subtrees, tree empty after delete
	if (t->left == NULL && t->right == NULL) {
		free(t);
		return NULL;
	}
	// if only right subtree, make it the new root
	else if (t->left == NULL && t->right != NULL) {
		BSTree hold = t->right;
        free(t);
		return hold;
	}
	// if only left subtree, make it the new root
	else if (t->left != NULL && t->right == NULL) {
        BSTree hold = t->left;
		free(t);
		return hold;
	}
	// else (t->left != NULL && t->right != NULL)
	// so has two subtrees
	// - find inorder successor
	// - move its value to root
	// - delete inorder successor node
	BSTLink parent = t;
	BSTLink succ = t->right; // not null!
	while (succ->left != NULL) {
		parent = succ;
		succ = succ->left;
	}
	t->value = succ->value;
	free(succ);
	if (parent == t)
		parent->right = succ->right;
	else
		parent->left = succ->right;
	return t;
}

// delete a value from a BSTree
BSTree BSTreeDelete(BSTree t, char *word)
{
	if (t == NULL)
		return NULL;
	else if (strcmp(word, t->key) < 0)
		t->left = BSTreeDelete(t->left, word);
	else if (strcmp(word, t->key) > 0)
		t->right = BSTreeDelete(t->right, word);
	else // (word == t->key)
		t = deleteRoot(t);
	return t;
}

static SetNode *newNode (char *url)   {
    SetNode *new = malloc(sizeof(SetNode));
    assert(new != NULL);
    new->url = strcpy(new->url, url);
    new->next = NULL;
    return new;
}

// Sorted node insert
BSTSet insertNode (BSTSet S, char *url)   {
    if (S == NULL)
        return newNode(url);
    if (strcmp(url, S->url) < 0)
        SetNode *n = newNode(url);
        n->next = S;
        return n;
    else if (strcmp(url, S->url) > 0)
        S->next = insertNode(S->next);
    else
        // Avoids duplicates - don't need to check
    return S;
}

BSTSet deleteNode (BSTSet S, char *url)   {
    if (S == NULL)  {
        return S;
    }
    if (strcmp(S->url, url) == 0)  {
        SetNode *temp = s->next;
        free(S);
        return temp;
    }

    S->next = deleteNode(S->next, url);

	return S;
}

void freeSet(BSTSet S) {
    if (S != NULL)  {
        freeSet(S->next);
        free(S);
    }
}
