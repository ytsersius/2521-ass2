// Interface to tfidfList
// Written by Steven Deng and Ying Zhong, October 2018

#ifndef TFIDFLIST_H
#define TFIDFLIST_H

#include <stdio.h>

typedef struct tfidfNode *tfidfList;

tfidfList newList(void);   //create new list

tfidfList listInsert (tfidfList, char *, char *); // insert a node

void insertURLCount(tfidfList, int, char *);
// inserts the number of urls a word appears in

tfidfList listDelete (tfidfList, char *); // delete a node

int inList(tfidfList, char *); // determines if a url is in the list

void showList (tfidfList); // shows the list

void listFree(tfidfList); // frees all memory from list

#endif
