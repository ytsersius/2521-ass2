#ifndef PAGERANKLIST_H
#define PAGERANKLIST_H

#include <stdbool.h>
#include "pageRank.h"

typedef struct Node *PRList;

//Linked List Operations
PRList insertLL(PRList, Vertex);
PRList deleteLL(PRList, Vertex);
bool inLL(PRList, int);
void freeLL(PRList);
void showLL(PRList);