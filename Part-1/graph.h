// Interface to graph ADT
// With reference to week09 lab files "Graph.c" & "Graph.h"
// Written by Steven Deng and Ying Zhong, October 2018

#ifndef GRAPH_H
#define GRAPH_H

#include <stdio.h>
#include <stdbool.h>
#include "graphList.h"

typedef struct GraphRep *Graph;

typedef struct GraphRep {
   List *edges;  // array of lists
   int    nV;     // #vertices
   int    nE;     // #edges
} GraphRep;

typedef int Vertex;

typedef struct Edge {   //when inserting or deleting
    Vertex v;           //from = edge.v; to = edge.w
    Vertex w;
} Edge;

typedef struct Connections  {   //number of incoming and
    int in;                     //outgoing links for a url
    int out;
} Connections;

// Graph Operations
Graph newGraph(int);
bool validV(Graph, Vertex); //validity check
void insertEdge(Graph, Edge);
void removeEdge(Graph, Edge);
bool adjacent(Graph, Vertex, Vertex); //adjacency check
void showGraph(Graph);
void freeGraph(Graph);

Connections nInOutLinks(Graph, Vertex); // links to and from vertex 
void printArray (Graph, Vertex); //print array
float Iu (Graph, Vertex); //return Iu (W_in) of a page
float Ou (Graph, Vertex); //return Ou (W_out) of a page
float sumIp (Graph, Vertex); //return sum of Ip (W_in) of a page
float sumOp (Graph, Vertex); //return sum of Op (W_out) of a page
float Win (Graph, Edge); //return W_in of a page
float Wout (Graph, Edge); //return W_out of a page
char *inArray (Graph, Vertex); //return array of incoming urls of a page
float PRWinWout (float, Graph, Edge); //return PR*Win*Wout for an edge
float sumPRWinWout (float, Graph, Vertex); //return sum of PR*Win*Wout for a page
float PageRank (Graph, Vertex, float, float); //return weighted pageRank for a page
float *PageRankW (Graph, float, float, int);

#endif
