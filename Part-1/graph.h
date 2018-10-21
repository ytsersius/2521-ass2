// Interface to graph ADT
// With reference to week09 lab files "Graph.c" & "Graph.h"
// Written by Steven Deng and Ying Zhong, October 2018

#ifndef GRAPH_H
#define GRAPH_H

#include <stdio.h>
#include <stdbool.h>

typedef struct GraphRep *Graph;

typedef int Vertex;

typedef struct Edge {   //when inserting or deleting
    Vertex v;           //from = edge.v; to = edge.w
    Vertex w;
} Edge;

// Graph Operations
Graph newGraph(int);
bool validV(Graph, Vertex); //validity check
void insertEdge(Graph, Edge);
void removeEdge(Graph, Edge);
bool adjacent(Graph, Vertex, Vertex); //adjacency check
void showGraph(Graph);
void freeGraph(Graph);

#endif
