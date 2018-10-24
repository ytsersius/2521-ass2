#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "setList.h"
#include "searchList.h"

#define MAX_RESULTS 30

int isMatch(char *word, char *argv[]);
void GetMatchedURLs(FILE *inv_idx, Set s, char *word);
int countMatches(char *url, Set s);
double findPageRank(char *url);

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

    free(word);
    fclose(inv_idx);

    if (matched_urls == NULL) {
        return ;
    }

    searchList ranked_urls = newList();
    // for each url
    Node *curr = matched_urls->elems;
    while (curr != NULL) {
        // count number of search terms matched
        int matches = countMatches(curr->url, matched_urls);
        // find page rank for that url
        double page_rank = findPageRank(curr->url);
        // insert into searcList
        ranked_urls = listInsert(ranked_urls, curr->url, matches, page_rank);

        curr = curr->next;
    }

    // output sorted urls less than 30
    searchNode *cur = ranked_urls;
    int i = 0;
    while (i < MAX_RESULTS && cur != NULL) {
        printf("%s\n", cur->link);
        cur = cur->next;
        i ++;
    }

    freeSet(matched_urls);
    listFree(ranked_urls);

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
            s = SetInsert(s, match_url);
        }
        buffer += pos;
    }

    free(match_url);
}

// counts number of times url appears in set
int countMatches(char *url, Set s) {
    int count = 0;
    Node *curr = s->elems;
    while (curr != NULL) {
        if (strcmp(curr->url, url) == 0) {
            count ++;
        }
        curr = curr->next;
    }

    return count;
}

double findPageRank(char *url) {
    FILE *pr_list = fopen("pagerankList.txt", "r");
    char line[1000];
    // Read a line and look for the word in the line
    while (fgets(line, 1000, pr_list)) {
        if (strstr(line, url) != NULL) {
            break;
        }
    }

    char temp[100];
    int outgoing;
    double page_rank;

    sscanf(line,"%s %d, %lf", temp, &outgoing, &page_rank);

    fclose(pr_list);

    return page_rank;
}
