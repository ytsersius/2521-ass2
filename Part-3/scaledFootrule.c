// Implementation of functions to read data given from
// url files.
// Written by Steven Deng and Ying Zhong, October 2018

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "Set.h"


Set GetCollection(int argc, char *argv[]);
int inCollection(char *string, Set s);
int *TSize(int argc, char *argv[]);
int *generateAlternatives(int *p, int index, int n);
int GetTRank(char *T, char *c);
double calculateTotalSFR(char *argv[], Set Collection, int *T_size,
    int *p);
double calculateScaledFootrule(int T_c, int T_size, int p, int n);
char *GetURL(Set Collection, int c);
int *copyArray(int *p, int n);

int main(int argc, char* argv[]) {
    if (argc <= 1) {
        printf("Please enter url rank files \n");
        return 0;
    }

    Set Collection = GetCollection(argc, argv);
    int n = Collection->nelems;
    int *T_s = TSize(argc, argv);

    int *p = calloc(n, sizeof(int));
    int *tried = calloc(n, sizeof(int));

    double minimum_distance = 1000; // int_max?

    int *p_minimum = generateAlternatives(argv, Collection, T_s,
        minimum, tried, p, 0);

    minimum_distance =  calculateTotalSFR(argv, Collection, T_size, p_minimum);
    printf("%f \n", minimum_distance);

    // print out urls in order of p_minimum[]
    int i = 0;
    Node *curr = Collection->elems;
    while (i < n) {
        // I'm not sure if this logic is right.
        if (p[i] == curr->vid) {
            char* url = GetURL(Collection, i + 1);
            printf("%s \n", url);
            i ++;
            curr = Collection->elems;
        }
        curr = curr->next;
    }

    return 0;
}

int *generateAlternatives(char *argv[], Set Collection, int *T_size,
    double minimum, int *tried, int *p, int index) {
    int n = Collection->nelems;
    if (index == n) {
        double total = calculateTotalSFR(argv, Collection, T_size, p);
        if (total < minimum) {
            minimum = total;
            int *p_minimum = copyArray(p, n);
        }
    }

    // j represents all the possible rankings p
    int j;
    for (j = 1; j < n; j ++) {
        if (!tried[j]) {
            p[index] = j;
            tried[j] = 1;
            // fill out the next index of p
            generateAlternatives(argv, Collection, T_size,
                minimum, tried, p, index + 1);
            tried[j] = 0;
        }
    }

    return p_minimum; // I'm not sure this is where you return
}

Set GetCollection(int argc, char *argv[]) {
    Set Collection = newSet();

    int i = 1;
    while (i < argc) {
        FILE *ranks = fopen(argv[i], "r");

        char line[1000];
        while (fscanf(ranks, "%s", line) != EOF) {
            char *url = calloc(strlen(line) + 1, sizeof(char));
            url = strcpy(url, line);
            if (!inCollection(url, Collection)) {
                SetInsert(Collection, url);
            }
            free(url);
        }

        fclose(ranks);
        i ++;
    }

    return Collection;
}

int inCollection(char *url_id, Set Collection) {
    Node *curr = Collection->elems;
    while (curr != NULL) {
        if (strcmp(curr->url, url_id) == 0) {
            return 1;
        }
        curr = curr->next;
    }

    return 0;
}

int *TSize(int argc, char *argv[]) {
    int *T_size = calloc((argc-1), sizeof(int));

    int i = 1;
    while (i < argc) {
        FILE *T = fopen(argv[i], "r");

        char line[1000];
        while (fscanf(T, "%s", line) != EOF) {
            T_size[i-1] ++;
        }

        fclose(T);
        i ++;
    }

    return T_size;
}

int GetTRank(char *T, char *c) {

    int rank = 1;
    int found = 0;

    FILE *f = fopen(T, "r");

    char line[1000];
    while (fscanf(f, "%s", line) != EOF) {
        if (strcmp(line, c) == 0) {
            found = 1;
            break;
        }
        rank ++;
    }

    fclose(f);

    // if the url c is not in file T[i], return 0
    if (found == 0) {
        return 0;
    }

    return rank;
}

// haven't tested
double calculateTotalSFR(char *argv[], Set Collection, int *T_size,
    int *p) {

    double totalSFR = 0;
    int n = Collection->nelems;

    int c = 0;
    // Go through all the nodes 1..n
    while (c < n) {
        char *url = GetURL(Collection, c);
        int i;
        // for every given rank file
        for (i = 1; i < argc; i ++) {
            int T_c = GetTRank(argv[i], url);
            double distance = calculateScaledFootrule(T_c, T_size[i], p[c], n);
            totalSFR = totalSFR + distance;
        }

        c ++;
    }

    return totalSFR;
}

// haven't tested
double calculateScaledFootrule(int T_c, int T_size, int p, int n) {
    // if c is not in the current T, don't sum
    if (T_c == 0) {
        return 0;
    }

    if (p == 0 || n == 0 || T_size == 0) {
        printf("error, invalid parameters in calculate SFR \n");
        return;
    }

    double SFRDistance = 0;

    SFRDistance = abs((T_c/T_size) - (p/n));

    return SFRDistance;
}

// Given an index c get the url at that index of the set
char *GetURL(Set Collection, int c) {
    Node *curr = Collection->elems;
    while (curr != NULL) {
        if (curr->id == c) {
            return curr->url;
        }
        curr = curr->next;
    }

    return NULL;
}

int *copyArray(int *p, int n) {
    int *dest = calloc(n, sizeof(char));

    int i;
    for (i = 0; i < n; i ++) {
        dest[i] = p[i];
    }

    return dest;
}
