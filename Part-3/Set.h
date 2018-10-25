// Interface to setList
// Written by Steven Deng and Ying Zhong, October 2018

#ifndef SET_H
#define SET_H

#include <stdio.h>
#include <stdbool.h>

typedef struct SetRep *Set;
typedef struct Node Node;

Set newSet(void);   //create new set

void freeSet(Set);  //free set memory

void SetInsert(Set, char *, int);   //add value into set

void SetDelete(Set, char *);    //remove value from set

void showSet(Set);

#endif
