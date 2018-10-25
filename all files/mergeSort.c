// C code for linked list merged sort
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

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
	if (a->matchCount > b->matchCount)
	{
		result = a;
		result->next = SortedMerge(a->next, b);
	}

	else if (a->matchCount < b->matchCount)
	{
		result = b;
		result->next = SortedMerge(a, b->next);
	}
	else if (a->tfidf > b->tfidf) {
		result = a;
		result->next = SortedMerge(a->next, b);
	}
	else if (a->tfidf < b->tfidf) {
		result = b;
		result->next = SortedMerge(a, b->next);
	}
	else if (strcmp(a->key, b->key) < 0) {
		result = a;
		result->next = SortedMerge(a->next, b);
	}
	else {
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
