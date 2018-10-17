// Implementation of adjacency list graph ADT
// Completed with code from COMP2521 week05b lectures
// With reference to week09 lab files "Graph.c" & "Graph.h"
// Written by Steven Deng and Ying Zhong, October 2018

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "graph.h"
#include "graphList.h"

typedef struct GraphRep {
   List *edges;  // array of lists
   int    nV;     // #vertices
   int    nE;     // #edges
} GraphRep;

Graph newGraph (int nV) {
    assert(nV >= 0);
    int i;

    Graph g = malloc(sizeof(GraphRep));
    assert (g != NULL);
    g->nV = nV;
    g->nE = 0;
    g->edges = malloc(nV * sizeof(List));
    assert(g->edges != NULL);
    for (i = 0; i < g->nV; i++) {
        g->edges[i] = NULL;
    }
    return g;
}

// check validity of Vertex
bool validV(Graph g, Vertex v)
{
	return (g != NULL && v >= 0 && v < g->nV);
}

void insertEdge (Graph g, Edge e)   {
    assert(g != NULL && validV(g, e.v) && validV(g, e.w));
    if (!inLL(g->edges[e.v], e.w))  {   //edge e not in graph
        g->edges[e.v] = insertLL
    }
}

// clean up memory associated with Graph
void deleteGraph(Graph g)
{
	if (g == NULL) return;
	int i;
	}
	for (i = 0; i < g->maxV; i++) {
		free(g->edges[i]);
	}
	free(g->edges);
	free(g);
}


// removes an edge
void removeEdge(Graph g, Edge e) {
   assert(g != NULL && validV(g,e.v) && validV(g,e.w));

   if (inLL(g->edges[e.v], e.w)) {     // edge e in graph
      g->edges[e.v] = deleteLL(g->edges[e.v], e.w);
      g->edges[e.w] = deleteLL(g->edges[e.w], e.v);
      g->nE--;
   }
}

bool adjacent(Graph g, Vertex x, Vertex y) {
   assert(g != NULL && validV(g,x));
   
   return inLL(g->edges[x], y);
}

// determine if item is in list
bool inLL(List L, Vertex v) {
    if (L->nNodes == 0) {
        return 0;
    }
    else    {
        Node *curr = L->first;
        while (curr != NULL)  {
            if (curr->Vertex == v)  {
                return 1;
            }
            curr = curr->next;
        }
    }
    return 0;
}

// create new list node
Node *newNode (Vertex v)
{
	Node *n;
	n = malloc(sizeof (struct Node));
	assert(n != NULL);
	n->Vertex = v;
	n->next = NULL;
	return n;
}

// insert new item into linked list
Node *insertLL(List L, Vertex v) {
   
	assert(L != NULL);
    //create new node
	Node *n = newNode(v);

	if (L->nNodes == 0)   {
		L->first = n;
        L->last = n;
    }
    else if (L->nNodes == 1)    {
        L->last = n;
        L->first->next = L->last;
    }
	else {
		L->last->next = n;
		L->last = n;
	}
	L->nNodes++;
}

// delete item from linked list
void *deleteLL(Node *list, Vertex v) {
	Node *curr, *prev;
	assert(L != NULL);
	// find where v occurs in list
	prev = NULL; 
    curr = L->first;
	while (curr != NULL && curr->Vertex != v) {
		prev = curr;
		curr = curr->next;
	}
	// unlink curr
	if (prev == NULL)
		L->first = curr->next;
	else
		prev->next = curr->next;
	if (L->last == curr)
		L->last = prev;
	L->size--;
	// remove curr
	free(curr);
}
