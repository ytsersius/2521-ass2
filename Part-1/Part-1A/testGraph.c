#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "graph.h"
#include "graphList.h"

int main () {

    Graph g = newGraph(20);
    Edge e;

    e.v = 0;
    e.w = 1;
    insertEdge(g, e, "url1", "body1");
    e.v = 1;
    e.w = 0;
    insertEdge(g, e, "url2", "body2");
    e.v = 1;
    e.w = 2;
    insertEdge(g, e, "url3", "body3");

    showGraph(g);

    return 0;

}
