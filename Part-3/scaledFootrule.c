// Implementation of functions to read data given from
// url files.
// Written by Steven Deng and Ying Zhong, October 2018

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

int totalSize(int argc, char *argv[]);
int countLines(FILE *f);
char **GetCollection(int argc, char *argv[]);
int inArray(char *string, char *Collection[], int size);
int CSize(char *Collection[]);
int *TSize(int argc, char *argv[]);
int *GetRanks(char *argv[], int argc, char **Collection);


int main(int argc, char* argv[]) {
    if (argc <= 1) {
        printf("Please enter url rank files");
    }

    char **Collection = GetCollection(argc, argv);

    int n = CSize(Collection);

    printf("n(cSize) is: %d", n);

    int i;
    for (i = 0; i < n; i ++) {
        printf("%s \n", Collection[i]);
    }

    return 0;
}

int totalSize(int argc, char *argv[]) {
    int size = 0;
    int i = 1;
    while (i < argc) {
        FILE *ranks = fopen(argv[i], "r");
        size = size + countLines(ranks);
        fclose(ranks);
        i ++;
    }

    return size;
}

int countLines(FILE *f) {
    char line[1000];
    int line_count = 0;
    while (fgets(line, 1000, f)) {
        line_count ++;
    }

    return line_count;
}

char **GetCollection(int argc, char *argv[]) {
    int size = totalSize(argc, argv);
    char Collection[size][1000];

    int i = 1;
    int j = 0;
    while (i < argc) {
        FILE *ranks = fopen(argv[i], "r");

        char *line;
        line = calloc(1000, sizeof(char));

        while (fgets(line, 1000, ranks)) {
            if (!inArray(line, Collection, size)) {
                strcpy(Collection[j], line);
                j ++;
            }
        }

        i ++;
    }

    return Collection;
}

int inArray(char *string, char *Collection[], int size) {
    int i = 0;
    while (Collection[i] != NULL) {
        if (strcmp(string, Collection[i]) == 0) {
            return 1;
        }
        i ++;
    }

    return 0;
}

int CSize(char **Collection) {
    int size = 0;
    int i = 0;
    while (strstr(Collection[i],"url") != NULL){
        size ++;
        i ++;
    }

    return size;
}
