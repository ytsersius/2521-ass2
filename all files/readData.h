// Interface to readData functions
// Written by Steven Deng and Ying Zhong, October 2018

#ifndef READDATA_H
#define READDATA_H

#include <stdio.h>
#include "graph.h"

// readData functions
Set GetCollection(void);
Graph GetGraph(Set);
void updateGraph(Graph, Set, Vertex, FILE *);
Vertex findVertexID(Set, char *);
/*
BSTree GetInvertedList(List url_list);
void updateInvertedIndex(BSTree, FILE *);
char *normalise(char *);
*/

#endif
