// Interface to inverted.c functions
// Written by Steven Deng and Ying Zhong, October 2018

#ifndef INVERTED_H
#define INVERTED_H

#include <stdio.h>

BSTree GetInvertedList(Set url_list);
void updateInvertedIndex(BSTree, FILE *, char *);
char *normalise(char *);

#endif
