#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <math.h>
#include "readData.h"
#include "setList.h"
#include "tfidfList.h"

#define MAX_RESULTS 30

int isMatch(char *word, char *argv[]);
void GetMatchedURLs(FILE *inv_idx, tfidfList L, char *word);
double calculateTf(char *word, char *url);
double calculateIdf(int N, int url_count);

int main(int argc, char *argv[]) {
    Set collection = GetCollection();
    int N = collection->nelems;

    // Open invertedIndex.txt for reading
    FILE *inv_idx = fopen("invertedIndex.txt", "r");

    tfidfList matched_URLs = newList();
    char temp[100];
    // search for matching words
    while (fscanf(inv_idx, "%s", temp) != EOF) {
        char *word = malloc(strlen(temp) + 1);
        word = strcpy(word, temp);
        // if found, store urls for that word
        if (isMatch(word, argv)) {
            GetMatchedURLs(inv_idx, matched_urls, word);
        }
    }

    free(word);
    fclose(inv_idx);

    if (matched_urls == NULL) {
        return ;
    }

    tfidfNode *curr = matched_URLs;
    tfidfNode *curr_word;
    while (curr != NULL) {
        curr_word = curr->matchWords;
        while (curr_word != NULL) {
            char *url = curr->key; // if i want to strcpy i need to malloc
            char *word = curr_word->key; // which is pretty ceebs
        // ^ not sure if this will cause errors with pointers
            int url_count = curr_word->matchCount;
            double tf = calculateTf(word, url);
            double idf = calculateIdf(N, url_count);
            curr->tfidf += tf * idf;

            curr_word = curr_word->next;
        }
        curr = curr->next;
    }

    // sort by matches, then if matches ==, by tfidf

    // print urls less than 30 with idf values

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
void GetMatchedURLs(FILE *inv_idx, tfidfList L, char *word) {
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
    int url_count = 0;
    while (sscanf(buffer,"%99s%n", temp, &pos) == 1) {
        char *match_url = malloc(strlen(temp) + 1);
        match_url = strcpy(match_url, temp);
        // Store the urls in the list
        if (strstr(match_url, "url") != NULL) {
            L = listInsert(L, match_url, word);
            url_count ++;
        }
        buffer += pos;
    }

    insertURLCount(L, url_count, word);
}

double calculateIdf(int N, int url_count) {
    double quotient = N/url_count;
    double idf = log10(quotient);

    return idf;
}

double calculateTf(char *word, char *url) {
    int word_freq = 0;
    int total_terms = 0;

    char *url_fname = calloc(strlen(url) + 5, sizeof(char));
    sprintf(url_fname, "%s.txt", url);
    // open the file for reading
    FILE *d = fopen(url_fname, "r");
    // read each word
    char temp[100];
    while(fscanf(d, "%s", temp) != EOF) {
        char *term = malloc(strlen(temp) + 1);
        term = strcpy(term, temp);
        if (strcmp(term, word) == 0) {
            word_freq ++;
        }
        // this condition needs to be modified lol
        if (strcmp(term, "#start") != 0 && strcmp(term, "#end") != 0
            && strstr(term, "url") == NULL) {
                total_terms ++;
            }
    }

    double tf = word_freq / total_terms;

    free(term);
    free (url_fname);
    fclose(d);

    return tf;
}
