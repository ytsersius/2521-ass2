// Interface to readData functions
// Written by Steven Deng and Ying Zhong, October 2018

#ifndef TESTGETGRAPH_H
#define TESTGETGRAPH_H

#include <stdio.h>

// readData functions
Set GetCollection(void);
Graph GetGraph(Set);
void updateGraph(Graph, Set, Vertex, FILE *);
Vertex findVertexID(Set, char *);

#endif