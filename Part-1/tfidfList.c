// tfidfList implementation for searchTfIdf.c function:
// Written by Steven Deng and Ying Zhong, October 2018

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "tfidfList.h"

typedef struct tfidfNode {
   char        *key;
   int          matchCount; // n of words matched by the url
   double       tfidf;      // n of docs a word is in for ->matchWords
   struct tfidfNode   *matchWords; // stores all the matched words
   struct tfidfNode   *next;
} tfidfNode;

static tfidfNode *newNode (char *key, char *word) {
    tfidfNode *new = malloc(sizeof(tfidfNode));
    assert(new != NULL);
    new->key = strcpy(new->key, key);
    new->matchCount = 1;
    new->tfidf = 0;
    new->next = NULL;
    new->matchWords = newMatchNode(word);

    return new;
}

static tfidfNode *newMatchNode (char *word) {
    tfidfNode *newMatch = malloc(sizeof(tfidfNode));
    newMatch->key = strcpy(newMatch->key, word);
    // update matchWords->matchCount in the body
    newMatch->tfidf = 0;
    newMatch->matchWords = NULL;
    newMatch->next = NULL;

    return newMatch;
}

tfidfList newList(void) {
    return NULL;
}

// sorted node insert
tfidfList listInsert (tfidfList L, char *key, char *word) {
    // avoid inserting duplicates
    if (inList(L, key)) {
        L->matchCount ++;
        L->matchWords->next = newMatchNode(word);
        return L;
    }
    if (L == NULL) {
        return newNode(key, word);
    }
    else if (strcmp(key, L->key) < 0) {
        tfidfNode *n = newNode(key, word);
        n->next = L;
        return n;
    }
    else if (strcmp(key, L->key) > 0) {
        L->next = listInsert(L->next, key, word);
    }
    return L;
}

// inserts the number of documents a word appears in
void insertURLCount(tfidfList L, int count, char *word) {
    tfidfNode *curr = L;
    tfidfNode *curr_word;
    while (curr != NULL) {
        curr_word = curr->matchWords;
        while (curr_word != NULL) {
            if (strcmp(curr_word->key, word) == 0) {
                curr_word->matchCount = count;
            }
                curr_word = curr_word->next;
        }
        curr = curr->next;
    }
}

tfidfList listDelete (tfidfList L, char *key)   {
    if (L == NULL)  {
        return L;
    }

    if (strcmp(L->key, key) == 0)  {
        tfidfNode *temp = L->next;
        free(L);

        return temp;
    }

    L->next = listDelete(L->next, key);
	return L;
}

int inList(tfidfList L, char *key)    {
    if (L == NULL)  {
        return 0;
    }
    if (strcmp(L->key, key) == 0)  {
        return 1;
    }

    return inList(L->next, key);
}

void showList (tfidfList L)    {
    if (L == NULL)  {
            putchar('\n');
    }
    else    {
        printf("%s - matchCount: %d - tfidf %.6f \n words:",
        L->key, L->matchCount, L->tfidf);

        tfidfNode *curr = L->matchWords;
        while (curr != NULL) {
            printf("%s ",curr->key);
            curr = curr->next;
        }

        putchar('\n');
        showList(L->next);
    }
}

void listFree(tfidfList L) {
    if (L != NULL)  {
        listFree(L->next);
        free(L);
    }
}
