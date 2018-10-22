#ifndef READDATA_H
#define READDATA_H

// Interface to Page Rank functions
// Written by Steven Deng and Ying Zhong, October 2018

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>

Connections nInOutLinks (Graph, Vertex); //links to vertex
double PageRankW (double, double, int);

#endif