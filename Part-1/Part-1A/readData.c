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
   Vertex       vID;
   struct Node *next;
} Node;

// -> Use struct set instead of list
typedef struct SetRep {
	int     nNodes;
	Node    first;
    Node    last;
} SetRep;

Set GetCollection(void) {
    FILE *collection = fopen("collection.txt", "r");
    Set url_list = newSet();

    char *url_id = calloc(6, sizeof(char));
    // I'm not sure how to dynamically allocate memory here

    // Read the url IDs into a variable
    int v = 1;
    while (fscanf(collection,"%s", url_id) != EOF) {
        insertNode(url_list, url_id, v);
        v ++;
    }

    free (url_id);
    fclose(collection);

    return url_list;
}

// Given a set url_list build a graph out of outgoing links
Graph GetGraph(Set url_list) {
    // Create an empty graph with nNodes vertices
    Graph g = newGraph(url_list->nNodes);
    Node *curr = url_list->first;

    // Traverse the set to read all url.txt files in the set
    while (curr != NULL) {
        // Store the url file name into a variable
        char *url_fname = calloc(10, sizeof(char)); // same problem as above
        sprintf(url_fname, "%s.txt", curr->url);

        // Read the url file and add outgoing links
        FILE *url_info = fopen(url_fname, "r");
        Vertex v = curr->vID;
        updateGraph(g, url_list, v, url_info);
        fclose(url_info);

        curr = curr->next;
    }

    return g;
}

// Given a url file, add outgoing links to the graph vertice
void updateGraph(Graph g, Set url_list, Vertex from, FILE *url_info) {
    char *out_url = calloc(6, sizeof(char));

    Edge e;
    e.v = from; // This is the current operating list
    // Read the url.txt file for outgoing links (word by word)
    while (fscanf(url_info,"%s", out_url) != EOF) {
        // If found an outgoing link
        if (strstr(out_url, "url") != NULL) {
            Vertex v_out = findVertexID(url_list, out_url);
            e.w = v_out;
            insertEdge(g, e);
        }
    }
}

// Finds the vertex ID corresponding to a url
// Returns 0 if failed
Vertex findVertexID(Set url_list, char *url) {
    Node *curr = url_list->first;
    while (curr != NULL) {
        if (strcmp(url, curr->url) == 0) {
            return curr->vID;
        }
        curr = curr->next;
    }

    return 0;
}

// For part 1b
BSTree GetInvertedList(List url_list) {
    // Create empty inverted list
    // For each url
        // Read url.txt file and update inverted index
}

// create an empty set
Set newSet(void) {


}

Node *newNode (char *url, Vertex vID) {

    return n;
}

Node *insertNode(Set L, char *url, Vertex vID) {


}

void *deleteNode(Node *item) {

    free();
}
