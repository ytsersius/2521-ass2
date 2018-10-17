#ifndef GRAPHLIST_H
#define GRAPHLIST_H

#include <stdbool.h>

typedef struct Node *List;

//Linked List Operations
List insertLL(List, int);
List deleteLL(List)
bool inLL(List, int);
void freeLL(List);
void showLL(List);

#endif
