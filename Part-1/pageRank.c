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

double Win (Edge e)		{
	assert(g->edges[e.v] != NULL && g->edges[e.w] != NULL);
	Connections c = nInOutLinks(g, v);
	
	int weightIN;

	weightIN = c.in 
}

double Wout (Edge e)	{

}

double PageRankW(double d, double diffPR, int maxIterations)	{
	Set s = GetCollection();
	Graph g = GetGraph(s);
	int N = g->nV;
	double PRWArray[N];

	int i;
	for (i = 0; i < N; i++)	{
		PRWArray[i] = 1.0/N;
	}

	i = 0;
	int interation = 0;
	double diff = diffPR;

	while (iteration < maxIterations && diff >= diffPR)	{
		for (i = 0; i < N; i++)	{
			PRWArray[i] = (1.0-d)/N + d*sumIncomingPages
		}
	}



}

size_t calculate_links(const matrix* m, size_t row)
{
	assert(m != NULL);
	assert(row <= m->size);

	size_t counter = 0;
	for (size_t i = 0; i < m->size; ++i)
	{
		counter += m->elements[i][row]; 
	}
	if(counter == 0)
	{
		return m->size;
	}
	assert(counter <= m->size);

	return counter;
}

float calculate_probability(const matrix* m, size_t i, size_t j)
{
	assert(m != NULL);
	float p = 1.0;
	size_t r = calculate_links(m, i);

	float a = (p * m->elements[i][j] / r) + ((1 - p) / m->size);

	return a;
}