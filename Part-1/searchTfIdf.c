#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "readData.h"
#include "setList.h"
#include "tfidfList.h"

#define MAX_RESULTS 30

int isMatch(char *word, char *argv[]);
void GetMatchedURLs(FILE *inv_idx, Set s, char *word);

int main(int argc, char *argv[]) {

    // Open invertedIndex.txt for reading
    FILE *inv_idx = fopen("invertedIndex.txt", "r");
    char temp[100];

    Set matched_urls = newSet();
    // search for matching words
    while (fscanf(inv_idx, "%s", temp) != EOF) {
        char *word = malloc(strlen(temp) + 1);
        word = strcpy(word, temp);
        // if found, store urls for that word
        if (isMatch(word, argv)) {
            GetMatchedURLs(inv_idx, matched_urls, word);
        }
    }

    fclose(inv_idx);

    if (matched_urls == NULL) {
        return ;
    }

    return 0;
}

// Determines if a word matches any of the arguments
int isMatch(char *word, char *argv[]) {
    int i = 1;
    while (argv[i] != NULL) {
        if strcmp(word, argv[i] == 0) {
            return 1;
        }
        i ++;
    }

    return 0;
}

// store urls for a matched term
void GetMatchedURLs(FILE *inv_idx, Set s, char *word) {
    char line[1000];
    // Read a line and look for the word in the line
    while (fgets(line, 1000, inv_idx)) {
        if (strstr(line, word) != NULL) {
            break;
        }
    }
    // Read the line for urls
    char *buffer = line;
    char temp[100];
    int pos;
    while (sscanf(buffer,"%99s%n", temp, &pos) == 1) {
        char *match_url = malloc(strlen(temp) + 1);
        match_url = strcpy(match_url, temp);
        // Store the urls in the set
        if (strstr(match_url, "url") != NULL) {
            SetInsert(s, match_url);
        }
        buffer += pos;
    }
}
