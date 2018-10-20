// This ADT is appended to the end of BSTree andcan be deleted
#include "BStree.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct SetNode {
   char        *url;
   struct Node *next;
} SetNode;

static SetNode *newNode (char *url)   {
    SetNode *new = malloc(sizeof(SetNode));
    assert(new != NULL);
    new->url = strcpy(new->url, url);
    new->next = NULL;
    return new;
}

// Sorted node insert
Set insertNode (Set S, char *url)   {
    if (S == NULL)
        return newNode(url);
    if (strcmp(url, S->url) < 0)
        SetNode *n = newNode(url);
        n->next = S;
        return n;
    else if (strcmp(url, S->url) > 0)
        S->next = insertNode(S->next);
    else
        // Avoids duplicates - don't need to check
    return S;
}

Set deleteNode (Set S, char *url)   {
    if (S == NULL)  {
        return S;
    }
    if (strcmp(S->url, url) == 0)  {
        SetNode *temp = s->next;
        free(S);
        return temp;
    }

    S->next = deleteNode(S->next, url);

	return S;
}

void freeSet(Set S) {
    if (S != NULL)  {
        freeSet(S->next);
        free(S);
    }
}
