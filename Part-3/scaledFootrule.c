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
int GetTRank(char *T, char *c);
double calculateTotalSFR(char *argv[], Set Collection, int *T_size,
    int *p);
double calculateScaledFootrule(int T_c, int T_size, int p, int n);

int main(int argc, char* argv[]) {
    if (argc <= 1) {
        printf("Please enter url rank files \n");
        return 0;
    }

    Set Collection = GetCollection(argc, argv);

    int *T_s = TSize(argc, argv);

    return 0;
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

    FILE *f = fopen(T, "r");

    char line[1000];
    while (fscanf(f, "%s", line) != EOF) {
        if (strcmp(line, c) == 0) {
            break;
        }
        rank ++;
    }

    fclose(f);

    return rank;
}

double calculateTotalSFR(char *argv[], Set Collection, int *T_size,
    int *p) {

        

    }

double calculateScaledFootrule(int T_c, int T_size, int p, int n) {


}
