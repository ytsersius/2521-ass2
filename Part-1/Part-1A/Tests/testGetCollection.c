
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "setList.h"

void GetCollection(Set s) {
    FILE *collection = fopen("collection.txt", "r");
    //Set s = newSet();

    char temp[100];


    // Read the url IDs into a variable
    while (fscanf(collection, "%s", temp) != EOF) {
        char *url_id = malloc(strlen(temp) + 1);
        memcpy(url_id, temp, strlen(temp));
		printf("%s\n", url_id);
        SetInsert(s, url_id);
    }

    //free (url_id); // Do we need this?
    fclose(collection);

}

int main()  {
    Set s = newSet();
	GetCollection(s);
    showSet(s);

    return 0;
}
