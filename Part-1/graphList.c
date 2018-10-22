#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "graphList.h"
#include "graph.h"

typedef struct adjNode {
    Vertex v;
    struct adjNode *next;
} adjNode;

adjNode *newNode (Vertex v)   {
    adjNode *new = malloc(sizeof(adjNode));
    assert(new != NULL);
    new->v = v;
    new->next = NULL;
    return new;
}

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

int nOutLL(List L)    {
    assert(L != NULL);
    int out = 0;
    adjNode *curr = L;
    while (curr != NULL) {
        curr = curr->next;
        out++;
    }
    return out;    
}

int nInLL(List L, Vertex v)   {
    assert(L != NULL);
    int in = 0;
    adjNode *curr = L;
    while (curr != NULL) {
        if (curr->v == v)   {
            in++;
        }
        curr = curr->next;
    }
    return in;
}

/*
int nInLLTotal(List L)    {
    assert (L != NULL);
    int sum = 0;
    adjNode *curr = L;
    while (curr != NULL)   {
        sum = sum + nInLL(curr, curr->v);
        curr = curr->next;
    }
    return sum;
}*/