// url List implementation for searchPageRank.c function:
// Written by Steven Deng and Ying Zhong, October 2018

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "urlList.h"

typedef struct searchNode {
   char        *link;
   int          matches;
   double       pageRank;
   struct searchNode   *next;
} searchNode;

static searchNode *newNode (char *url, int matches, double pageRank) {
    searchNode *new = malloc(sizeof(searchNode));
    assert(new != NULL);
    new->link = strcpy(new->link, url);
    new->matches = matches;
    new->pageRank = pageRank;
    new->next = NULL;
    return new;

}

searchList newList(void) {
    return NULL;
}

// sorted node insert
searchList listInsert (searchList L, char *url, int matches, double pageRank) {
    // avoid duplicates
    if (inList(L, url)) {
        return L;
    }

    if (L == NULL) {
        return newNode(url, matches, pageRank);
    }

    else if (matches > L->matches) {
        searchNode *n = newNode(url, matches, pageRank);
        n->next = L;
        return n;
    }

    else if (matches < L->matches) {
        L->next = listInsert(L->next, url, matches, pageRank);
    }

    else if (pageRank > L->pageRank) {
        searchNode *n = newNode(url, matches, pageRank);
        n->next = L;
        return n;
    }

    else if(pagerank < L->pageRank) {
        L->next = listInsert(L->next, url, matches, pageRank);
    }

    // assume that we won't get 2 urls with the same pagerank

    return L;
}

searchList listDelete (searchList L, char *url)   {
    if (L == NULL)  {
        return L;
    }

    if (strcmp(L->link, url) == 0)  {
        searchNode *temp = L->next;
        free(L);
        return temp;
    }

    L->next = listDelete(L->next, url);
	return L;
}

int inList(searchList L, char *url)    {
    if (L == NULL)  {
        return 0;
    }
    if (strcmp(L->link, url) == 0)  {
        return 1;
    }

    return inList(L->next, url);
}

void showList (searchList L)    {
    if (L == NULL)  {
            putchar('\n');
    }
    else    {
        printf("%s - matches: %d - pagerank %.7f \n",
        L->link, L->matches, L->pageRank);
        showList(L->next);
    }
}

void listFree(searcList L) {
    if (L != NULL)  {
        listFree(L->next);
        free(L);
    }
}
