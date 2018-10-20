// Implementation of functions to read data given from
// url files.
// Written by Steven Deng and Ying Zhong, October 2018

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>

#include "graph.h"
#include "graphList.h"
#include "Set.h"
#include "BSTree.h"

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

// TO DO:
// - Finish set ADT + test
// - Test GetCollection
// - Test GetGraph (might as well do it in the pageRank.c file)
// - Write invertedList

Set GetCollection(void) {
    FILE *collection = fopen("collection.txt", "r");
    Set url_list = newSet();

    char *url_id = calloc(100, sizeof(char));
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
    Graph url_graph = newGraph(url_list->nNodes);

    // Traverse the set to read all url.txt files in the set
    Node *curr = url_list->first;
    while (curr != NULL) {
        // Store the url file name into a variable
        char *url_fname = calloc(100, sizeof(char)); // same problem as above
        sprintf(url_fname, "%s.txt", curr->url);

        // Read the url file and add outgoing links
        FILE *url_info = fopen(url_fname, "r");
        Vertex v = curr->vID;
        updateGraph(url_graph, url_list, v, url_info);
        fclose(url_info);

        curr = curr->next;
    }

    return url_graph;
}

// Given a url file, add outgoing links to the graph vertice
void updateGraph(Graph g, Set url_list, Vertex from, FILE *url_info) {
    char *out_url = calloc(100, sizeof(char));

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
BSTree GetInvertedList(Set url_list) {
    BSTree inv_tree = newBSTree();

    Node *curr = url_list->first;
    while (curr != NULL) {
        // Store the url file name into a variable
        char *url_fname = calloc(100, sizeof(char));
        sprintf(url_fname, "%s.txt", curr->url);

        // Read url.txt file
        FILE *url_info = fopen(url_fname, "r");
        updateInvertedIndex(inv_tree, url_info, curr->url);
        fclose(url_info);

        curr = curr->next;
    }

    return inv_tree;
}

void updateInvertedIndex(BSTree inv_tree, FILE *url_info, char *url) {
    char temp[100]; // temporary text buffer

    // Read url.txt file for words
    while (fscanf(url_info, "%s", temp) != EOF) {
        char *word = strdup(temp);
        word = normalise(word);
        // insert key into tree
        inv_tree = BSTreeInsert(inv_tree, word);
        // insert url into urlSet at the right node
        BSTNode *t = BSTreeFind(inv_tree, word));
        t->urlSet = insertNode(inv_tree->urlSet, url);
    }
}


char *normalise(char *word) {
    // we aren't going to have whitespaces anyway
    // because fscanf only reads up to a whitespace
    int i = 0;
    char *ptr = word;
    while (isspace(word[i]) {
        word[i] = '\0';
        ptr ++;
        i ++;
    }

    word = ptr;

    while (!isspace(word[i])) {
        i ++; // crappy implementation - change if u want
    }

    word[i] = '\0'

    // Convert all upper case to lower case
    i = 0;
    while (word[i] != '\0') {
        if (word[i] >= 'A' && word[i] <= 'Z'){
            int offset = word[i] -'A';
            word[i] = 'a' + offset;
        }
        i ++;
    }
    // Remove ending punctuation marks
    int size = strlen(word);
    if (word[size] != '.' && word[size] != ','
        && word[size] != ';' && word[size] != '?') {
            word[size] = '\0';
        }
        
    return word;
}

// create an empty set
Set newSet(void) {


}

Node *newNode (char *url, Vertex vID) {

    return n;
}

Node *insertNode(Set L, char *url, Vertex vID) {


}

Node *deleteNode(Set L, Vertex vID) {


}

void freeSet(Set L) {

    free();
}
