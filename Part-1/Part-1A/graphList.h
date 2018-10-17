#ifndef GRAPHLIST_H
#define GRAPHLIST_H

#include <stdbool.h>

typedef struct Node *List;

//Linked List Operations
List insertLL(List, Vertex, char *, char *);
List deleteLL(List, int);
bool inLL(List, int);
void freeLL(List);
void showLL(List);

#endif
