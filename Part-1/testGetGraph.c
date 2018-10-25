
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "setList.h"
#include "graph.h"
#include "testGetGraph.h"
#include "pageRank.h"
#include "pageRankList.h"

Set GetCollection(void) {
    FILE *collection = fopen("collection.txt", "r");
    Set s = newSet();

    char temp[100];
    // Read the url IDs into a variable
    while (fscanf(collection,"%s", temp) != EOF) {
        char *url_id = malloc(strlen(temp) + 1);
        url_id = strcpy(url_id, temp);
        SetInsert(s, url_id);
        free (url_id);
    }

    fclose(collection);

    return s;
}

// Given a set s build a graph out of outgoing links
Graph GetGraph(Set s) {
    // Create an empty graph with nNodes vertices
    Graph g = newGraph(s->nelems);

    // Traverse the set to read all url.txt files in the set
    Node *curr = s->elems;
    char *url_fname;
    while (curr != NULL) {
        // Store the url file name into a variable
        url_fname = calloc(strlen(curr->url) + 5, sizeof(char));
        sprintf(url_fname, "%s.txt", curr->url);

        // Read the url file and add outgoing links
        FILE *url_info = fopen(url_fname, "r");
        Vertex v = curr->vID;
        updateGraph(g, s, v, url_info);
        fclose(url_info);

        curr = curr->next;
    }

    free(url_fname);

    return g;
}

// Given a url file, add outgoing links to the graph vertice
void updateGraph(Graph g, Set s, Vertex from, FILE *url_info) {
    char temp[100];

    Edge e;
    e.v = from; // This is the current operating list
    // Read the url.txt file for outgoing links (word by word)
    char *out_url;
    while (fscanf(url_info, "%s", temp) != EOF) {
        out_url = malloc(strlen(temp) + 1);
        out_url = strcpy(out_url, temp);
        // If found an outgoing link
        if (strstr(out_url, "url") != NULL) {
            Vertex v_out = findVertexID(s, out_url);
            e.w = v_out;
            insertEdge(g, e);
        }
        free(out_url);
    }
}

// Finds the vertex ID corresponding to a url
// Returns 0 if failed
Vertex findVertexID(Set s, char *url) {
    Node *curr = s->elems;
    while (curr != NULL) {
        if (strcmp(url, curr->url) == 0) {
            return curr->vID;
        }
        curr = curr->next;
    }

    return 0;
}

int main()  {
    Set s = GetCollection();
    showSet(s);
    Graph g = GetGraph(s);
    showGraph(g);
    return 0;
}
