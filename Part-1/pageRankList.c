#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct Node {
    Vertex v;
    float PR;
    struct Node *next;
} Node;

Node *newNode ()   {
    Node *new = malloc(sizeof(Node));
    assert(new != NULL);
    new->v = 0;
    new->PR = 0;
    new->next = NULL;
    return new;
}

PRList insertLL (PRList L, Vertex v, float PR)   {
    if (inLL(L, v)) {
        return L;
    }
    Node *n = newNode();
    n->v = v;
    n->PR = PR;
	n->next = L;
    return n;
}

/* To sort the linked list */
void SelectionSort(node *head)
{
	node *start = head;
	node *traverse;
	node *min;
	
	while(start->link)
	{
		min = start;
		traverse = start->link;
		
		while(traverse)
		{
			/* Find minimum element from array */ 
			if( min->data > traverse->data )
			{
				min = traverse;
			}
			
			traverse = traverse->link;
		}
		swap(start,min);			// Put minimum element on starting location
		start = start->link;
	}
} 
 
/* swap data field of linked list */
void swap(node *p1, node*p2)
{
	int temp = p1->data;
	p1->data = p2->data;
	p2->data = temp;
}

PRList deleteLL (PRList L, Vertex v)   {
    if (L == NULL)  {
        return L;
    }
    if (L->v == v)  {
        return L->next;
    }

    L->next = deleteLL(L->next, v);
	return L;
}

bool inLL(PRList L, int n)    {
    if (L == NULL)  {
        return false;
    }
    if (L->v == n)  {
        return true;
    }

    return inLL(L->next, n);
}

void showLL (PRList L)    {
    if (L == NULL)  {
            putchar('\n');
    }
    else    {
        printf("%d - ", L->v);
        showLL(L->next);
    }
}

void freeLL(PRList L) {
    if (L != NULL)  {
        freeLL(L->next);
        free(L);
    }
}