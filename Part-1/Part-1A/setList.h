// Interface to setList
// Written by Steven Deng and Ying Zhong, October 2018

#ifndef SET_H
#define SET_H

#include <stdio.h>
#include <stdbool.h>
#include "graph.h"

typedef struct SetRep *Set;

Set newSet();   //create new set

void freeSet(Set);  //free set memory

void SetInsert(Set, char *, Vertex);   //add value into set

void SetDelete(Set, Vertex);    //remove value from set

void showSet(Set);

#endif