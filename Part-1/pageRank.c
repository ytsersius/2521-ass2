// Implementation of functions for Page Rank from graph
// Written by Steven Deng and Ying Zhong, October 2018

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>
#include "setList.h"
#include "graph.h"
#include "readData.h"

Connections nInOutLinks (Graph g, Vertex v) {
    assert(g->edges[v] != NULL);
    Connections c;
    c.out = nOutLL(g->edges[v]);
    c.in = 0;
    int i = 0;
    while (i < g->nV && g->edges[i] != NULL)    {
        if (i != v) {
            c.in = c.in + nInLL(g->edges[i], v);
        }   
        i++;
    }
    return c;
}

float Iu (Graph g, Vertex v)    {
    float sum = 0;
    int i = 0;
    while (i < g->nV && g->edges[i] != NULL)    {
        if (i != v) {
            sum = sum + nInLL(g->edges[i], v);
        }
        i++;
    }
    return sum;
}

float sumIp (Graph g, Vertex v)   {
    char *array = outArray(g->edges[v]);
    int i;
    float sum = 0;
    for (i = 0; i < nOutLL(g->edges[v]); i++)  {
        sum = sum + Iu(g, array[i]);
    }
    return sum;
}

float Win (Graph g, Edge e) {
    float I_u = Iu(g, e.w);
    float sum_Ip = sumIp(g, e.v);
    return I_u/sum_Ip;
}

float Ou (Graph g, Vertex v)    {
    assert(g->edges[v] != NULL);
    float out = nOutLL(g->edges[v]);
    return out;
}

float sumOp (Graph g, Vertex v)   {
    char *array = outArray(g->edges[v]);
    int i;
    float sum = 0;
    for (i = 0; i < nOutLL(g->edges[v]); i++)  {
        sum = sum + Ou(g, array[i]);
    }
    return sum;
}

float Wout (Graph g, Edge e) {
    float O_u = Ou(g, e.w);
    float sum_Op = sumOp(g, e.v);
    return O_u/sum_Op;
}


/*
char *PageRankW (float d, float diffPR, int maxIterations)   {
    int N = g->nV;
	char PRWArray[N];

    int i;
	for (i = 0; i < N; i++)	{
		PRWArray[i] = 1.0/N;
	}

	int iteration = 0;
	float diff = diffPR;
    i = 0;
	while (iteration < maxIterations && diff >= diffPR)	{
		for (i = 0; i < N; i++)	{
			PRWArray[i] = (1.0-d)/N + d*sumIncomingPages
		}

        iteration ++;
	}
    return PWArray;
}*/

float PageRank (float PR, float d, float diffPR, int maxIteration, Graph g, Vertex v)    {
    
    float diff = diffPR;
    int N = g->nV;
    int iteration = 0;

    while (iteration < maxIteration && diff >= diffPR)  {
        float temp = PR;
        PR = (1-d)/N + d * sumPRWinWout(PR, d, diffPR, maxIteration, g, v);
        for (int i = 0; i < N; i++) {
            diff = diff + fabs(PR - temp);
        }
    }
    
    return PR;
}

float sumPRWinWout (float PR, float d, float diffPR, int maxIteration, Graph g, Vertex v)   {
    char *array = inArray(g, v);
    float sum = 0;
    int i;
    for (i = 0; i < Iu(g, v); i++)    { 
        sum = sum + (PageRank(PR, d, diffPR, maxIteration, g, v) * Win(g, e) * Wout(g, e));
    }
    return sum;
}

// return array of incoming urls to a page
char *inArray(Graph g, Vertex v)   {
    char *in = malloc(nInLL(g->edges[v], v));
    assert(in != NULL);

    int i = 0;
    int j = 0;
    while (i < g->nV && g->edges[i] != NULL)    {
        if (i != v && inLL(g->edges[i], v)) {
            in[j] = i;
            j++;
        }   
        i++;
    }
    return in;
}

// print array of incoming urls to a page
void printArray (Graph g, Vertex v) {
    char *ar = inArray(g, v);
    int i;
    for (i = 0; i < Iu(g, v); i++)    {
        printf("%d\n", ar[i]);
    }
}