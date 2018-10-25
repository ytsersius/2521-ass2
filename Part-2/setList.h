// Interface to setList
// Written by Steven Deng and Ying Zhong, October 2018

#ifndef SETLIST_H
#define SETLIST_H

#include <stdio.h>
#include <stdbool.h>

typedef struct SetRep *Set;

typedef int Vertex;

Set newSet(void);   //create new set

void freeSet(Set);  //free set memory

void SetInsert(Set, char *);   //add value into set

void SetDelete(Set, char *);    //remove value from set

void showSet(Set);

#endif
