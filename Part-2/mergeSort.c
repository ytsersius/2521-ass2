// C code for linked list merged sort
#include<stdio.h>
#include<stdlib.h>

/* function prototypes */
struct tfidfNode* SortedMerge(struct tfidfNode* a, struct tfidfNode* b);
void FrontBackSplit(struct tfidfNode* source,
		struct tfidfNode** frontRef, struct tfidfNode** backRef);

/* sorts the linked list by changing next pointers (not data) */
void MergeSort(struct tfidftfidfNode** headRef) {
	struct tfidfNode* head = *headRef;
	struct tfidfNode* a;
	struct tfidfNode* b;

	/* Base case -- length 0 or 1 */
	if ((head == NULL) || (head->next == NULL))
	{
		return;
	}

	/* Split head into 'a' and 'b' sublists */
	FrontBackSplit(head, &a, &b);

	/* Recursively sort the sublists */
	MergeSort(&a);
	MergeSort(&b);

	/* answer = merge the two sorted lists together */
	*headRef = SortedMerge(a, b);
}

/* See https://www.geeksforgeeks.org/?p=3622 for details of this
function */
struct tfidfNode* SortedMerge(struct tfidfNode* a, struct tfidfNode* b) {
	struct tfidfNode* result = NULL;

	/* Base cases */
	if (a == NULL)
		return(b);
	else if (b==NULL)
		return(a);

	/* Pick either a or b, and recur */
	if (a->data <= b->data)
	{
		result = a;
		result->next = SortedMerge(a->next, b);
	}
	else
	{
		result = b;
		result->next = SortedMerge(a, b->next);
	}
	return(result);
}

/* UTILITY FUNCTIONS */
/* Split the tfidfNodes of the given list into front and back halves,
	and return the two lists using the reference parameters.
	If the length is odd, the extra tfidfNode should go in the front list.
	Uses the fast/slow pointer strategy. */
void FrontBackSplit(struct tfidfNode* source,
		struct tfidfNode** frontRef, struct tfidfNode** backRef)
{
	struct tfidfNode* fast;
	struct tfidfNode* slow;
	slow = source;
	fast = source->next;

	/* Advance 'fast' two tfidfNodes, and advance 'slow' one tfidfNode at each iteration */
	while (fast != NULL) {
		fast = fast->next;
		if (fast != NULL) {
			slow = slow->next;
			fast = fast->next;
		}
	}

	/* 'slow' is before the midpoint in the list, so split it in two
	at that point. */
	*frontRef = source;
	*backRef = slow->next;
	slow->next = NULL; // I don't understand what this is for
}

/* Function to print tfidfNodes in a given linked list */
void printList(struct tfidfNode *tfidfNode) {
	while(tfidfNode!=NULL) {
		printf("%d ", tfidfNode->data);
		tfidfNode = tfidfNode->next;
	}
}

/* Function to insert a tfidfNode at the beginging of the linked list */
void push(struct tfidfNode** head_ref, int new_data)
	{
	/* allocate tfidfNode */
	struct tfidfNode* new_tfidfNode =
				(struct tfidfNode*) malloc(sizeof(struct tfidfNode));

	/* put in the data */
	new_tfidfNode->data = new_data;

	/* link the old list off the new tfidfNode */
	new_tfidfNode->next = (*head_ref);

	/* move the head to point to the new tfidfNode */
	(*head_ref) = new_tfidfNode;
}

/* Drier program to test above functions*/
int main()
	{
	/* Start with the empty list */
	struct tfidfNode* res = NULL;
	struct tfidfNode* a = NULL;

	/* Let us create a unsorted linked lists to test the functions
	Created lists shall be a: 2->3->20->5->10->15 */
	push(&a, 15);
	push(&a, 10);
	push(&a, 5);
	push(&a, 20);
	push(&a, 3);
	push(&a, 2);

	/* Sort the above created Linked List */
	MergeSort(&a);

	printf("Sorted Linked List is: \n");
	printList(a);

	getchar();
	return 0;
}
