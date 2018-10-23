#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "graph.h"
#include "graphList.h"
#include "pageRank.h"

int main () {

    Graph g = newGraph(20);
    Edge e;

    e.v = 0;
    e.w = 1;
    insertEdge(g, e);
    e.v = 1;
    e.w = 0;
    insertEdge(g, e);
    e.v = 1;
    e.w = 2;
    insertEdge(g, e);
    e.v = 2;
    e.w = 1;
    insertEdge(g, e);
    e.v = 3;
    e.w = 1;
    insertEdge(g, e);
    e.v = 4;
    e.w = 1;
    insertEdge(g, e);
    e.v = 0;
    e.w = 2;
    insertEdge(g,e);

    Connections c = nInOutLinks(g, 1);
    printf("For Vertex 1:\nTotal no. of URLS\nfrom: %d\nto: %d\n", c.in, c.out);

    c = nInOutLinks(g, 2);
    printf("For Vertex 2:\nTotal no. of URLS\nfrom: %d\nto: %d\n", c.in, c.out);

    c = nInOutLinks(g, 3);
    printf("For Vertex 3:\nTotal no. of URLS\nfrom: %d\nto: %d\n", c.in, c.out);

    c = nInOutLinks(g, 4);
    printf("For Vertex 4:\nTotal no. of URLS\nfrom: %d\nto: %d\n", c.in, c.out);

    showGraph(g);

    

    e.v = 1;
    e.w = 0;

    printf("Test W_in:\nsumIp: %f\nIu: %f\nWin: %f\n", sumIp(g, 1), Iu(g, 0), Win(g, e)); 

    printf("Test W_out:\nSumOp: %f\nOu: %f\nWout: %f\n", sumOp(g, 1), Ou(g, 0), Wout(g, e));

    printArray(g, 1);

    return 0;

}
