// Interface to searchList
// Written by Steven Deng and Ying Zhong, October 2018

#ifndef SEARCHLIST_H
#define SEARCHLIST_H

#include <stdio.h>

typedef struct searchNode *searchList;

searchList newList(void);   //create new list

searchList listInsert (searchList, char *, int, double);
// sorted list insert

searchList listDelete (searchList, char *); // delete a node

int inList(searchList L, char *url); // determines if a url is in the list

void showList (searchList L); // shows he list

void listFree(searchList L); // frees all memory from list

#endif
