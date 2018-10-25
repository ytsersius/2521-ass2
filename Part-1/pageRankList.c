#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "pageRankList.h"

Node *newNode ()   {
    Node *new = malloc(sizeof(Node));
    assert(new != NULL);
    new->vID = 0;
    new->PR = 0;
    new->next = NULL;
    return new;
}

struct ListRep {
	int     nelems;
    Node    *elems;
};

int isValid(List L)  {
    if (L == NULL)  {
        return 0;
    }
    else    {
        return 1;
    }
}

// List Operations

//  create new List
List newList(void)    {
    List L = malloc(sizeof(struct ListRep));
    assert(L != NULL);
    L->nelems = 0;
    L->elems = NULL;
    return L;
}

void freeList(List L) {
    Node* tmp;
    while (L->elems != NULL) {
       tmp = L->elems;
       L->elems = L->elems->next;
       free(tmp);
    }
}


void ListInsert(List L, Vertex v, float PR) {
    assert(isValid(L));
    Node *new = malloc(sizeof(Node));
    assert(new != NULL);
    new->vID = v;
    new->PR = PR;
    new->next = L->elems;
    L->elems = new;
	L->nelems++;
}

void ListDelete(List L, Vertex v) {
}

void showList(List L) {
    assert(isValid(L));
    printf("Show List:\n{\n");
    Node *curr;
    for (curr = L->elems; curr != NULL; curr = curr->next)  {
        printf("vID = %d - %f\n", curr->vID, curr->PR);
    }
    printf("}\n");
	printf("Size of the List: %d\n", L->nelems);
}

// =======Merge Sort========= start

//Split the nodes of the given list into front and back halves, 
void FrontBackSplit (Node* source, Node** frontRef, Node** backRef) { 
    Node *fast; 
    Node *slow; 
    slow = source; 
    fast = source->next; 
  
     //Advance 'fast' two nodes, and advance 'slow' one node 
    while (fast != NULL)    { 
        fast = fast->next; 
        if (fast != NULL)   { 
            slow = slow->next; 
            fast = fast->next; 
        } 
    } 
  
     //'slow' is before the midpoint in the list, so split it in two 
    //at that point. 
    *frontRef = source; 
    *backRef = slow->next; 
    slow->next = NULL; 
} 

// merge two halves of the linked list
Node *SortedMerge (Node *a, Node *b)    { 
    Node *result = NULL; 
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

//sorts the linked list by changing next pointers (not data) 
void MergeSort(struct Node** headRef) { 
    Node *head = *headRef; 
    Node *a; 
    Node *b; 
  
     //Base case -- length 0 or 1 
    if ((head == NULL) || (head->next == NULL)) { 
        return; 
    } 
    // Split head into 'a' and 'b' sublists 
    FrontBackSplit(head, &a, &b);  
     //Recursively sort the sublists 
    MergeSort(&a); 
    MergeSort(&b); 
     //answer = merge the two sorted lists together 
    *headRef = SortedMerge(a, b); 
} 

// return merge sort List
void mMergeSort(List L)  {
    MergeSort(&L->elems);
}

// ========Merge Sort========== end

// ========Selection Sort=========== not used
/*
// swap data field of linked list 
void swap (Node *p1, Node *p2)   {
	float tempPR = p1->PR;
    Vertex tempvID = p1->vID;

	p1->PR = p2->PR;
    p1->vID = p2->vID;
	p2->PR = tempPR;
    p2->vID = tempvID;
}

// To sort the linked list 
void SelectionSort(List L)  {
	Node *start = L->elems;
	Node *traverse;
	Node *max;
	
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
