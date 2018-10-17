#include "graphList.h"
#include "graph.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

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
    new->url = url;
    new->text = text;
    new->next = NULL;
    return new;
}

List insertLL (List L, Vertex v, char *url, char *text)   {
    if (inLL(L, v)) {
        return L;
    }

    Node *new = newNode (v, url, text);
    new->next = L;
    L = new;
    return L;
}

List deleteLL (List L, int n)   {
    if (L == NULL)  {
        return L;
    }
    if (L->v == n)  {
        return L->next;
    }

    L->next = deleteLL(L->next, n);
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
