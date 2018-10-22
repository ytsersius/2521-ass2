#ifndef GRAPHLIST_H
#define GRAPHLIST_H

#include <stdbool.h>
#include "graph.h"

typedef struct adjNode *List;

//Linked List Operations
List insertLL(List, Vertex);
List deleteLL(List, Vertex);
bool inLL(List, int);
void freeLL(List);
void showLL(List);
int nOutLL(List); //find number of outgoing URLs from vertex
int nInLL(List L, Vertex v); //find number of incomnig URLS to vertex

#endif
