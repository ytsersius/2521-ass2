// Implementation of functions to read data given from
// url files.
// Written by Steven Deng and Ying Zhong, October 2018

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "graph.h"
#include "graphList.h"

typedef struct Node {
   char        *url;
   struct Node *next;
} Node;

typedef struct ListRep {
	int     nNodes;
	Node    first;
    Node    last;
} ListRep;

List GetCollection(void) {
    FILE *collection = fopen("collection.txt", "r");
    List url_list = newList();

    // Read the url IDs
    char *url_id;
    while (fscanf(collection,"%s", url_id) != 0) {
        insertLL(url_list, url_id);
    }

    fclose(collection);

    return url_list;
}

Graph GetGraph(List url_list) {
    Graph g = newGraph(url_list->nNodes);
    Node *curr = url_list->first;

    int i = 0;
    while (curr != NULL) {
        char *url_fname;
        sprintf(url_fname, "%s.txt", curr->url)
        FILE *url_info = fopen(url_fname, "r");
        updateGraph(g, curr, url_info);
        fclose(url_info);
        curr = curr->next;
        i ++;
    }

    return g;
}

updateGraph(Graph g, Node *curr, FILE *url_info, int i) {
    // need to get to the relevant text (skip #section 1)
    edges[i]->v = i;

    char *url_id;
    while (fscanf(url_info,"%s", url_id) != 0) {
        if (strstr(url_id, "url") != NULL) {
            insertEdge(g, )
        }
    }

}

// For part 1b
BSTree GetInvertedList(List url_list) {
    // Create empty inverted list
    // For each url
        // Read url.txt file and update inverted index
}

// create an empty list
List newList(void) {


}

Node *newNode (char *url, char *text) {

    return n;
}

Node *insertLL(List L, char *url) {


}

void *deleteLL(Node *item, char *id) {

    free();
}
