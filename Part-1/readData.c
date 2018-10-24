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
#include "setList.h"
#include "BSTree.h"

// TO DO:
// - Test GetInvertedList (do this in inverted.c)

Set GetCollection(void) {
    FILE *collection = fopen("collection.txt", "r");
    Set url_list = newSet();

    char temp[100];
    // Read the url IDs into a variable
    while (fscanf(collection,"%s", temp) != EOF) {
        char *url_id = malloc(strlen(temp) + 1);
        url_id = strcpy(url_id, temp);
        SetInsert(url_list, url_id);
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
        char *url_fname = calloc(strlen(curr->url) + 5, sizeof(char));
        sprintf(url_fname, "%s.txt", curr->url);

        // Read the url file and add outgoing links
        FILE *url_info = fopen(url_fname, "r");
        Vertex v = curr->vID;
        updateGraph(url_graph, url_list, v, url_info);
        fclose(url_info);

        curr = curr->next;
    }

    free(url_fname);

    return url_graph;
}

// Given a url file, add outgoing links to the graph vertice
void updateGraph(Graph g, Set url_list, Vertex from, FILE *url_info) {
    char temp[100];

    Edge e;
    e.v = from; // This is the current operating list
    // Read the url.txt file for outgoing links (word by word)
    while (fscanf(url_info, "%s", temp) != EOF) {
        char *out_url = malloc(strlen(temp) + 1);
        out_url = strcpy(out_url, temp);
        // If found an outgoing link
        if (strstr(out_url, "url") != NULL) {
            Vertex v_out = findVertexID(url_list, out_url);
            e.w = v_out;
            insertEdge(g, e);
        }
    }

    free(out_url);
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

// Given a url list, generate an invertedList
BSTree GetInvertedList(Set url_list) {
    BSTree inv_tree = newBSTree();

    Node *curr = url_list->first;
    while (curr != NULL) {
        // Store the url file name into a variable
        char *url_fname = calloc(strlen(curr->url) + 5, sizeof(char));
        sprintf(url_fname, "%s.txt", curr->url);

        // Read url.txt file
        FILE *url_info = fopen(url_fname, "r");
        updateInvertedIndex(inv_tree, url_info, curr->url);
        fclose(url_info);

        curr = curr->next;
    }

    free(url_fname);

    return inv_tree;
}

// *Need to figure out how to only read relevant text
void updateInvertedIndex(BSTree inv_tree, FILE *url_info, char *url) {
    char temp[100]; // temporary text buffer

    // Read url.txt file for words
    while (fscanf(url_info, "%s", temp) != EOF) {
        char *word1 = malloc(strlen(temp) + 1);
        word1 = strcpy(word1, temp);

        fscanf(url_info, "%s", temp);
        char *word2 = malloc(strlen(temp) + 1);
        word2 = strcpy(word2, temp);
        if (strcmp(word1, "#start") != 0 && strcmp(word1, "#end") != 0
            && strstr(word1, "url") == NULL && strcmp(word2, "Section-1") != 0
            && strcmp(word2, "Section-2") != 0) {
            word1 = normalise(word1);
            word2 = normalise(word2);
            // insert key into tree
            inv_tree = BSTreeInsert(inv_tree, word1);
            inv_tree = BSTreeInsert(inv_tree, word2);
            // insert url into urlSet at the right node
            BSTNode *t = BSTreeFind(inv_tree, word1));
            t->urlSet = insertNode(t->urlSet, url);

            t = BSTreeFind(inv_tree, word2);
            t->urlSet = insertNode(t->urlSet, url);
        }

        free(word1);
        free(word2);
    }
}

char *normalise(char *word) {
    int size = strlen(word);
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

    while (!isspace(word[i]) && i < size) {
        i ++; // crappy implementation - change if u want
    }

    word[i] = '\0';

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
    if (word[size] != '.' && word[size] != ','
        && word[size] != ';' && word[size] != '?') {
            word[size] = '\0';
        }

    return word;
}
