#ifndef GRAPHLIST_H
#define GRAPHLIST_H

#include <stdbool.h>
#include "graph.h"

typedef struct Node *List;

//Linked List Operations
List insertLL(List, Node);
List deleteLL(List, int);
bool inLL(List, int);
void freeLL(List);
void showLL(List);

#endif
