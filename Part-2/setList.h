// Interface to setList
// Written by Steven Deng and Ying Zhong, October 2018

#ifndef SETLIST_H
#define SETLIST_H

#include <stdio.h>
#include <stdbool.h>
typedef int Vertex;

typedef struct Node {
   char        *url;
   Vertex       vID;
   struct Node *next;
} Node;

struct SetRep {
	int     nelems;
    Node    *elems;
};
typedef struct SetRep *Set;



Set newSet(void);   //create new set

void freeSet(Set);  //free set memory

void SetInsert(Set, char *);   //add value into set

void SetDelete(Set, char *);    //remove value from set

void showSet(Set);

#endif
