#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "setList.h"
#include ""

int main()  {
    Set s = newSet();

    char *url = "url0";
    Vertex vID = 0;
    SetInsert(s, url, vID);

    url = "url1";
    vID = 1;
    SetInsert(s, url, vID);

    url = "url2";
    vID = 2;
    SetInsert(s, url, vID);

    url = "url3";
    vID = 3;
    SetInsert(s, url, vID);

    showSet(s);
}