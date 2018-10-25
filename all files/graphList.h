#ifndef GRAPHLIST_H
#define GRAPHLIST_H

#include <stdbool.h>

typedef struct adjNode *List;
typedef int Vertex;

//Linked List Operations
List insertLL(List, Vertex);
List deleteLL(List, Vertex);
bool inLL(List, int);
void freeLL(List);
void showLL(List);
int nOutLL(List); //find number of outgoing URLs from vertex
int nInLL(List, Vertex); //find number of incomnig URLS to vertex
char *outArray(List); 

#endif
