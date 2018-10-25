
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "setList.h"

Set GetCollection(void) {
    FILE *collection = fopen("collection.txt", "r");
    Set url_list = newSet();

    char temp[100];
    // Read the url IDs into a variable
    int i = 0;
    while (fscanf(collection,"%s", temp) != EOF) {
        char *url_id = malloc(strlen(temp) + 1);
        url_id = strcpy(url_id, temp);
        SetInsert(url_list, url_id);
        free (url_id);
        i++;
    }

    fclose(collection);

    return url_list;
}

char *getURL (Set s, Vertex v) {
    Vertex i;
    char *url = malloc(sizeof(char *));
    Node *curr = s->elems;
    for (i = s->nelems - 1; i >= 0; i--) {
        if (i == v) {
            url = strcpy(url, curr->url);
        }
        curr = curr->next;
    }
    return url;
}

int main()  {
    Set s = GetCollection();
    showSet(s);
    char *url = getURL(s, 6);
    printf("%s\n", url);

    return 0;
}
