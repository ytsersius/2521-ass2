// url List implementation for searchPageRank.c function:
// Written by Steven Deng and Ying Zhong, October 2018

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "urlList.h"

typedef struct URLNode {
   char        *link;
   int          matches;
   double       pageRank;
   struct URLNode   *next;
} URLNode;

List insertLL (List L, Vertex v)   {
    if (inLL(L, v)) {
        return L;
    }

    adjNode *n = newNode(v);
	n->next = L;
    return n;
}

List deleteLL (List L, Vertex v)   {
    if (L == NULL)  {
        return L;
    }
    if (L->v == v)  {
        return L->next;
    }

    L->next = deleteLL(L->next, v);
	return L;
}

bool inLL(List L, int n)    {
    if (L == NULL)  {
        return false;
    }
    if (L->v == n)  {
        return true;
    }

    return inLL(L->next, n);
}

void showLL (List L)    {
    if (L == NULL)  {
            putchar('\n');
    }
    else    {
        printf("%d - ", L->v);
        showLL(L->next);
    }
}

void freeLL(List L) {
    if (L != NULL)  {
        freeLL(L->next);
        free(L);
    }
}
