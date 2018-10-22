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
    for (i = 0; i < g->nV; i++) {	//newNode needs to go here
        g->edges[i] = NULL;			//g->edges[i] != NULL
    }

    return g;
}

// check validity of Vertex
bool validV(Graph g, Vertex v)
{
	return (g != NULL && v >= 0 && v < g->nV);
}

void insertEdge (Graph g, Edge e)   {
    //from = e.v; to = e.w
    assert(g != NULL && validV(g, e.v) && validV(g, e.w));
    if (!inLL(g->edges[e.v], e.w))  {   //edge e not in graph
        g->edges[e.v] = insertLL(g->edges[e.v], e.w);
        g->nE++;
    }
}

void removeEdge (Graph g, Edge e)   {
    //from = e.v; to = e.w
    assert (g != NULL && validV(g, e.v) && validV(g, e.w));
    if (inLL(g->edges[e.v], e.w))   {   //edge e in graph
        g->edges[e.v] = deleteLL(g->edges[e.v], e.w);
        g->nE--;
    }
}

bool adjacent (Graph g, Vertex v, Vertex w)   {
    assert(g != NULL && validV(g,v));
    return inLL(g->edges[v], w);
}

void showGraph (Graph g)    {
    assert(g != NULL);
    int i;
    for (i = 0; i < g->nV; i++) {
        printf("%d - ", i);
        showLL(g->edges[i]);
    }
    printf("Number of vertices: %d\n", g->nV);
    printf("Number of edges: %d\n", g->nE);
}

void freeGraph (Graph g)    {
    assert(g != NULL);
    int i;

    for (i = 0; i < g->nV; i++) {
        freeLL(g->edges[i]);
    }
    free(g);
}



