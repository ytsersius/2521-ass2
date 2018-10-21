// Set List implementation for readData.c function: 
// Set GetCollection (void);
// Written by Steven Deng and Ying Zhong, October 2018


#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include "setList.h"

typedef struct Node {
   char        *url;
   Vertex       vID;
   struct Node *next;
} Node;

struct SetRep {
	int     nelems;
    Node    *elems;
};

// is set valid
int isValid(Set s)  {
    if (s == NULL)  {
        return 0;
    }
    else    {
        return 1;
    }
}

// Set Operations

//  create new set
Set newSet()    {
    Set s = malloc(sizeof(struct SetRep));
    assert(s != NULL);
    s->nelems = 0;
    s->elems = NULL;
    return s;
} 

void freeSet(Set s) {
    assert(s != NULL);
    while (s->elems != NULL)    {
        SetDelete(s);
    }
    free(s);
}


void SetInsert(Set s, char * url, Vertex vID) {
    assert(isValid(s));
    Node *new = malloc(sizeof(Node));
    assert(new != NULL);
    new->url = url;
    new->vID = vID;
    new->next = s->elems;
    s->elems = new;
}

void SetDelete(Set s) {
    assert(s->nelems > 0);
    if (s->elems == 1)  {
        free(s->elems);
        s->nelems--;
    }
    else    {
        Node *curr = s->elems;
        s->elems = s->elems->next;
        free(curr);
        s->elems--;
    }    
}

void showSet(Set s) {
    assert(isValid(s));
    printf("{");
    Node *curr;
    for (curr = s->elems; curr != NULL; curr = curr->next)  {
        printf("%d", curr-> value);
        if (curr->next != NULL) {
            printf(",");
        }
    }
    printf("}");
}