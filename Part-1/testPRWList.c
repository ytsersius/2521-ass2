#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "setList.h"
#include "pageRank.h"
#include "pageRankList.h"

Set GetCollection(void) {
    FILE *collection = fopen("collection.txt", "r");
    Set url_list = newSet();

    char temp[100];
    // Read the url IDs into a variable
    int i = 0;
    while (fscanf(collection,"%s", temp) != EOF) {
        char *url_id = malloc(strlen(temp) + 1);
        url_id = strcpy(url_id, temp);
        SetInsert(url_list, url_id);
        free (url_id);
        i++;
    }

    fclose(collection);

    return url_list;
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


int main()  {
    Set s = GetCollection();
    showSet(s);
    Graph g = GetGraph(s);

    float d = 0.85;
    float diffPR = 0.0001;
    int maxIteration = 100;

    float *PRWarray = PageRankArray(g, d, diffPR, maxIteration);

    int i;
    printf("Start of PRW\n");
    for (i = 0; i < s->nelems; i++) {
        printf("%.7f\n", PRWarray[i]);
    }

    PRList L = PRWList(s, s->nelems, PRWarray);
    showList(L);
    mMergeSort(L);
    showList(L);

    PRNode *curr = L->elems;
    while (curr != NULL)    {
        printf("%d, %s, %0.f, %.7f\n", curr->vID, curr->url, Ou(g, curr->vID), curr->PR);
        curr = curr->next;
    }
    
    FILE *fp = fopen("pagerankList.txt" ,"w");
    curr = L->elems;
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

