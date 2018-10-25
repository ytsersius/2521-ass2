#ifndef PAGERANK_H
#define PAGERANK_H

// Interface to Page Rank functions
// Written by Steven Deng and Ying Zhong, October 2018

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>
#include "pageRankList.h"
#include "graph.h"
#include "graphList.h"

Connections nInOutLinks (Graph, Vertex); //links to vertex
float *PageRankArray (Graph, float, float, int);
float PageRank (Graph g, Vertex v, float PR, float d);
PRList PRWList (Set s, int N, float *array);
char *getURL (Set s, Vertex v);



float Iu (Graph, Vertex); //return Iu (W_in) of a page
float Ou (Graph, Vertex); //return Ou (W_out) of a page
float sumIp (Graph, Vertex); //return sum of Ip (W_in) of a page
float sumOp (Graph, Vertex); //return sum of Op (W_out) of a page
float Win (Graph, Edge); //return W_in of a page
float Wout (Graph, Edge); //return W_out of a page
char *inArray (Graph, Vertex); //return array of incoming urls of a page
float PRWinWout (float, Graph, Edge); //return PR*Win*Wout for an edge
float sumPRWinWout (float, Graph, Vertex); //return sum of PR*Win*Wout for a page



#endif