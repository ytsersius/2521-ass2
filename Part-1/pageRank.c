// Implementation of functions for Page Rank from graph
// Written by Steven Deng and Ying Zhong, October 2018

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "setList.h"
#include "graph.h"
#include "graphList.h"
#include "readData.h"
#include "pageRank.h"
#include "pageRankList.h"

// return PageRank for a page
float PageRank (Graph g, Vertex v, float PR, float d)    {
    int N = g->nV;
    PR = ((1.0-d)/N) + (d * sumPRWinWout(PR, g, v));
    return PR;
}

// return array of page rank for all urls
float *PageRankArray (Graph g, float d, float diffPR, int maxIteration)   {
    int N = g->nV;
    float *PRarray = malloc(N*sizeof(float));
    int i;
    for (i = 0; i < N; i++) {
        PRarray[i] = 1.0/N;
    }
    int iteration = 0;
    float diff = diffPR;
    while (iteration < maxIteration && diff >= diffPR)  {
        float sumDiff = 0;
        for (i = 0; i < g->nV; i++) {
            float temp = PRarray[i];
            PRarray[i] = PageRank(g, i, PRarray[i], d);
            sumDiff = sumDiff + fabs(PRarray[i] - temp);
        }
        diff = sumDiff;
        iteration++;
    }
    return PRarray;
}


int main (int argc, char **argv) {

    //create set from "collection.txt"
    Set s = GetCollection();
    //create graph from "url___.txt's"
    Graph g = GetGraph(s);

    float d = atof(argv[1]);
    float diffPR = atof(argv[2]);
    int maxIteration = atoi(argv[3]);

    //create array of vertices with weighted PR
    float *PRWarray = PageRankArray(g, d, diffPR, maxIteration);
    //transform array into list with URLs
    PRList L = PRWList(s, s->nelems, PRWarray);
    //merge sort list
    mMergeSort(L);

    //output "pagerankList.txt"
    FILE *fp = fopen("pagerankList.txt" ,"w");
    PRNode *curr = L->elems;
    while (curr != NULL)    {
        fprintf(fp, "%s, %0.f, %.7f", curr->url, Ou(g, curr->vID), curr->PR);
        if (curr->next != NULL) {
            fprintf(fp, "\n");
        }
        curr = curr->next;
    }
    fclose(fp);
    
    return 0;
    
}

// create List of PRW given array
PRList PRWList (Set s, int N, float *array) {
    PRList L = newList();
    int i;
    for (i = 0; i < N; i++) {
        ListInsert(L, i, getURL(s, i), array[i]);
    }
    return L;
}

// return URL given vertex number
char *getURL (Set s, Vertex v) {
    Vertex i;
    char *url = malloc(sizeof(char *));
    Node *curr = s->elems;
    for (i = s->nelems - 1; i >= 0; i--) {
        if (i == v) {
            url = strcpy(url, curr->url);
        }
        curr = curr->next;
    }
    return url;
}

// ====== PageRank calculation functions =====

//find no. of incoming links for a page (Iu)
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

//find sum of (no. of incoming links of outgoing URLS) (IP)
float sumIp (Graph g, Vertex v)   {
    char *array = outArray(g->edges[v]);
    int i;
    float sum = 0;
    for (i = 0; i < nOutLL(g->edges[v]); i++)  {
        sum = sum + Iu(g, array[i]);
    }
    return sum;
}

//return Win for an edge
float Win (Graph g, Edge e) {
    float I_u = Iu(g, e.w);
    float sum_Ip = sumIp(g, e.v);
    return I_u/sum_Ip;
}

//find 
float Ou (Graph g, Vertex v)    {
    if (g->edges[v] == NULL)    {
        return 0.5;
    }
    float out = nOutLL(g->edges[v]);
    if (out == 0)   {
        return 0.5;
    }
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

// return PR*Win*Wout for a given edge
float PRWinWout (float PR, Graph g, Edge e) {
    return PR*Win(g, e)*Wout(g, e);
}

// return sum of PRWinWout for a page
float sumPRWinWout (float PR, Graph g, Vertex v)   {
    char *array = inArray(g, v);
    float sum = 0;
    int i;
    Edge e;
    for (i = 0; i < Iu(g, v); i++)    {
        e.v = array[i];
        e.w = v;
        sum = sum + PRWinWout(PR, g, e);
    }
    return sum;
}

// ===== PageRank calculation functions end =====


//return number of incoming and outgoing links
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

