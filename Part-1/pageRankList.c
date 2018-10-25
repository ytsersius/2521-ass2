#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "pageRankList.h"

int isValidPR(PRList L)  {
    if (L == NULL)  {
        return 0;
    }
    else    {
        return 1;
    }
}

// List Operations

//  create new List
PRList newList(void)    {
    PRList L = malloc(sizeof(struct PRListRep));
    assert(L != NULL);
    L->nelems = 0;
    L->elems = NULL;
    return L;
}

void freeList(PRList L) {
    PRNode* tmp;
    while (L->elems != NULL) {
       tmp = L->elems;
       L->elems = L->elems->next;
       free(tmp);
    }
}


void ListInsert(PRList L, Vertex v, char *url, float PR) {
    assert(isValidPR(L));
    PRNode *new = malloc(sizeof(PRNode));
    assert(new != NULL);
    new->vID = v;
    new->url = malloc(sizeof(char*));
    new->url = strcpy(new->url, url);
    new->PR = PR;
    new->next = L->elems;
    L->elems = new;
	L->nelems++;
}

void ListDelete(PRList L, Vertex v) {
}

void showList(PRList L) {
    assert(isValidPR(L));
    printf("Show List:\n{\n");
    PRNode *curr;
    for (curr = L->elems; curr != NULL; curr = curr->next)  {
        printf("vID = %d - %s - %f\n", curr->vID, curr->url, curr->PR);
    }
    printf("}\n");
	printf("Size of the List: %d\n", L->nelems);
}

// =======Merge Sort========= start

//Split the PRNodes of the given List into front and back halves, 
void FrontBackSplit (PRNode* source, PRNode** frontRef, PRNode** backRef) { 
    PRNode *fast; 
    PRNode *slow; 
    slow = source; 
    fast = source->next; 
  
     //Advance 'fast' two PRNodes, and advance 'slow' one PRNode 
    while (fast != NULL)    { 
        fast = fast->next; 
        if (fast != NULL)   { 
            slow = slow->next; 
            fast = fast->next; 
        } 
    } 
  
     //'slow' is before the midpoint in the List, so split it in two 
    //at that point. 
    *frontRef = source; 
    *backRef = slow->next; 
    slow->next = NULL; 
} 

// merge two halves of the linked List
PRNode *SortedMerge (PRNode *a, PRNode *b)    { 
    PRNode *result = NULL; 
     //Base cases 
    if (a == NULL)  {
        return b; 
    } 
    else if (b == NULL)   {
        return a; 
    }
     //Pick either a or b, and recur 
    if (a->PR >= b->PR) { 
        result = a; 
        result->next = SortedMerge(a->next, b); 
    } 
    else    { 
        result = b; 
        result->next = SortedMerge(a, b->next); 
    } 
    return result; 
} 

//sorts the linked List by changing next pointers (not data) 
void MergeSort(struct PRNode** headRef) { 
    PRNode *head = *headRef; 
    PRNode *a; 
    PRNode *b; 
  
     //Base case -- length 0 or 1 
    if ((head == NULL) || (head->next == NULL)) { 
        return; 
    } 
    // Split head into 'a' and 'b' subLists 
    FrontBackSplit(head, &a, &b);  
     //Recursively sort the subLists 
    MergeSort(&a); 
    MergeSort(&b); 
     //answer = merge the two sorted Lists together 
    *headRef = SortedMerge(a, b); 
} 

// return merge sort List
void mMergeSort(PRList L)  {
    MergeSort(&L->elems);
}

// ========Merge Sort========== end




// ========Selection Sort=========== not used
/*
// swap data field of linked List 
void swap (PRNode *p1, PRNode *p2)   {
	float tempPR = p1->PR;
    Vertex tempvID = p1->vID;

	p1->PR = p2->PR;
    p1->vID = p2->vID;
	p2->PR = tempPR;
    p2->vID = tempvID;
}

// To sort the linked List 
void SelectionSort(List L)  {
	PRNode *start = L->elems;
	PRNode *traverse;
	PRNode *max;
	
	while (start->next != NULL)     {
		max = start;
		traverse = start->next;
		
		while (traverse != NULL)     {
			// Find minimum element from array 
			if( max->PR < traverse->PR )    {
				max = traverse;
			}
			traverse = traverse->next;
		}
		swap(start, max); // Put minimum element on starting location
		start = start->next;
	}
} */
