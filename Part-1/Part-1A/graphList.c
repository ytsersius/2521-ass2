#include "graphList.h"
#include "graph.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct Node {
    Vertex v;
    char *url;
    char *text;
    struct Node *next;
} Node;

Node *newNode (Vertex v, char *url, char* text)   {
    Node *new = malloc(sizeof(Node));
    assert(new != NULL);
    new->v = v;
    new->url = strdup(url);
    new->text = strdup(text);
    new->next = NULL;
    return new;
}

List insertLL (List L, Node n)   {
    if (inLL(L, n->v)) {
        return L;
    }

    n->next = L;
    return n;
}

List deleteLL (List L, int n)   {
    if (L == NULL)  {
        return L;
    }
    if (L->v == n)  {
        //free(L->url);
        //free(L->text);
        return L->next;
    }

    L->next = deleteLL(L->next, n);
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
        printf("%d ", L->v);
        showLL(L->next);
    }
}

void freeLL(List L) {
    if (L != NULL)  {
        freeLL(L->next);
        free(L);
    }
}
