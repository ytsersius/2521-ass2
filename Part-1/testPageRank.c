#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "graph.h"
#include "graphList.h"
#include "pageRank.h"

int main () {

    Graph g = newGraph(7);
    Edge e;

    e.v = 0;
    e.w = 1;
    insertEdge(g, e);
    e.v = 0;
    e.w = 2;
    insertEdge(g,e);
    e.v = 0;
    e.w = 3;
    insertEdge(g,e);

    e.v = 1;
    e.w = 4;
    insertEdge(g, e);

    e.v = 2;
    e.w = 4;
    insertEdge(g, e);
    e.v = 2;
    e.w = 5;
    insertEdge(g, e);
    e.v = 2;
    e.w = 1;
    insertEdge(g, e);
    e.v = 2;
    e.w = 6;
    insertEdge(g, e);

    e.v = 3;
    e.w = 0;
    insertEdge(g, e);
    e.v = 3;
    e.w = 6;
    insertEdge(g, e);
    e.v = 3;
    e.w = 5;
    insertEdge(g, e);
    e.v = 3;
    e.w = 4;
    insertEdge(g, e);

    e.v = 4;
    e.w = 1;
    insertEdge(g, e);
    e.v = 4;
    e.w = 2;
    insertEdge(g, e);
    e.v = 4;
    e.w = 6;
    insertEdge(g, e);

    Connections c = nInOutLinks(g, 1);
    printf("For Vertex 1:\nTotal no. of URLS\nfrom: %d\nto: %d\n", c.in, c.out);

    c = nInOutLinks(g, 2);
    printf("For Vertex 2:\nTotal no. of URLS\nfrom: %d\nto: %d\n", c.in, c.out);

    c = nInOutLinks(g, 3);
    printf("For Vertex 3:\nTotal no. of URLS\nfrom: %d\nto: %d\n", c.in, c.out);

    c = nInOutLinks(g, 4);
    printf("For Vertex 4:\nTotal no. of URLS\nfrom: %d\nto: %d\n", c.in, c.out);

    showGraph(g);

    

    e.v = 4;
    e.w = 6;

    printf("Edge 4-6:\nTest W_in:\nsumIp: %f\nIu: %f\nWin: %f\n", sumIp(g, 4), Iu(g, 6), Win(g, e)); 

    printf("Test W_out:\nSumOp: %f\nOu: %f\nWout: %f\n", sumOp(g, 4), Ou(g, 6), Wout(g, e));

    printArray(g, 1);

    float PR = 0.5;
    e.v = 0;
    e.w = 1;
    float prw = PRWinWout(PR, g, e);
    printf("Edge 0-1: %f\n", prw);

    e.v = 2;
    prw = PRWinWout(PR, g, e);
    printf("Edge 2-1: %f\n", prw);

    e.v = 3;
    prw = PRWinWout(PR, g, e);
    printf("Edge 3-1: %f\n", prw);

    e.v = 4;
    prw = PRWinWout(PR, g, e);
    printf("Edge 4-1: %f\n", prw);

    PR = 1.0/7;
    float sumPRW = sumPRWinWout(PR, g, 1); 
    printf("sumPRWinWout: %.10f\n", sumPRW);

    float d = 0.85;
    float pageRankW = PageRank(g, 1, PR, d);
    printf("PageRank: %f\n", pageRankW);

    float *array = PageRankW(g, d, 0.00001, 1000);

    int i;
    printf("Start of PRW\n");
    for (i = 0; i < 7; i++) {
        printf("%.7f\n", array[i]);
    }

    

    return 0;  

}
