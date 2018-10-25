#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "Set.h"
#include "BSTree.h"
#include "readData.h"

int main (void) {
    Set url_list = GetCollection();
    BSTree inv_idx = GetInvertedList(url_list);

    FILE *fp = fopen("invertedIndex.txt", "w+");
    BSTreeInfix(inv_idx, fp);

    freeSet(url_list);
    dropBSTree(inv_idx);
    
    fclose(fp);

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
        free(url_fname);
    }

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
