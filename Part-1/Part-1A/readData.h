// Interface to readData functions
// Written by Steven Deng and Ying Zhong, October 2018

#ifndef READDATA_H
#define READDATA_H

#include <stdio.h>

typedef struct SetRep *Set;

// readData functions
Set GetCollection(void);
Graph GetGraph(Set);
void updateGraph(Graph, Set, Vertex, FILE *);
Vertex findVertexID(Set, char *);
BSTree GetInvertedList(List url_list);
void updateInvertedIndex(BSTree, FILE *);

// Set ADT functions
Set newSet(void);
Node *newNode(char *, Vertex);
Node *insertNode(Set, char *, Vertex);
Node *deleteNode(Set, Vertex);
void freeSet(Set);

#endif
