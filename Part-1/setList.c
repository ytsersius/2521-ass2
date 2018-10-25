// Set List implementation for readData.c function:
// Set GetCollection (void);
// Written by Steven Deng and Ying Zhong, October 2018


#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>
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
Set newSet(void)    {
    Set s = malloc(sizeof(struct SetRep));
    assert(s != NULL);
    s->nelems = 0;
    s->elems = NULL;
    return s;
}

void freeSet(Set s) {
    Node* tmp;
    while (s->elems != NULL) {
       tmp = s->elems;
       s->elems = s->elems->next;
       free(tmp->url);
       free(tmp);
    }
}


void SetInsert(Set s, char *url) {
    assert(isValid(s));
    Node *new = malloc(sizeof(Node));
    assert(new != NULL);
    new->url = malloc(sizeof(char*));
    new->url = strcpy(new->url, url);
    new->vID = s->nelems;
    new->next = s->elems;
    s->elems = new;
	s->nelems++;
}

void SetDelete(Set s, char *url) {
}

void showSet(Set s) {
    assert(isValid(s));
    printf("Show Set:\n{\n");
    Node *curr;
    for (curr = s->elems; curr != NULL; curr = curr->next)  {
        printf("vID = %d - %s\n", curr->vID, curr->url);
    }
    printf("}\n");
	printf("Size of the set: %d\n", s->nelems);
}
