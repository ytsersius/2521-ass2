#include <stdio.h>
#include "graphList.h"
#include "graph.h"


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

    Connections c = nInOutLinks(g, 1);
    printf("For Vertex 1:\nTotal no. of URLS\nfrom: %d\nto: %d\n", c.in, c.out);

    c = nInOutLinks(g, 2);
    printf("For Vertex 2:\nTotal no. of URLS\nfrom: %d\nto: %d\n", c.in, c.out);

    c = nInOutLinks(g, 3);
    printf("For Vertex 3:\nTotal no. of URLS\nfrom: %d\nto: %d\n", c.in, c.out);

    c = nInOutLinks(g, 4);
    printf("For Vertex 4:\nTotal no. of URLS\nfrom: %d\nto: %d\n", c.in, c.out);

    showGraph(g);

	printArray(g, 1);

    int N = 20;
    float PRarray[N];
    int i;
    for (i = 0; i < N; i++) {
        PRarray[i] = 1.0/N;
        printf("%f\n", PRarray[i]);
    }

    return 0;

}
