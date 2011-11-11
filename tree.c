#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "tree.h"
#include "table.h"
#define TRUE 1
#define FALSE 0

/*Create a new node for a four-way tree*/
TNode*
TNode_new(void) {
	TNode * tp;
	if((tp = (TNode*) malloc(sizeof(TNode))) != NULL) {
		tp->t1 = NULL;
		tp->t2 = NULL; 
		tp->t3 = NULL;
		tp->t4 = NULL;
		return tp;
	}
	fprintf(stderr, "Error allocating memory. Terminating.\n");
	exit(EXIT_FAILURE);
}

/*Given a four-way tree, populate the possibilities for the first
digit in ph_no into the tree, then recurse on any new nodes
to ensure their children get populated with the next digit's possibilities*/
TNode* 
TNode_populate(TNode *root, char *ph_no) {

	/*If a null tree is passed in, then return NULL*/	
	if(root == NULL) 
		return root;
	/*If a valid letter exists as first possibility for this digit*/
	if(table_lookup(*ph_no, 1)) {
		
		/*Create new node for tree with matched letter*/
		root->t1 = TNode_new();
		root->t1->key = table_lookup(*ph_no, 1);
		/*Add it to the tree*/
		TNode_populate(root->t1, ph_no + 1);
	}

	/*If a valid letter exists as second possibility for this digit*/
	if(table_lookup(*ph_no, 2)) {
		/*Create new node for tree with matched letter*/
		root->t2 = TNode_new();
		root->t2->key = table_lookup(*ph_no, 2);
		/*Add it to the tree*/
		TNode_populate(root->t2, ph_no + 1);
	}

	/*If a valid letter exists as third possibility for this digit*/
	if(table_lookup(*ph_no, 3)) {
		/*Create new node for tree with matched letter*/
		root->t3 = TNode_new();
		root->t3->key = table_lookup(*ph_no, 3);
		/*Add it to the tree*/
		TNode_populate(root->t3, ph_no + 1);
	}

	/*If a valid letter exists as fourth possibility for this digit*/
	if(table_lookup(*ph_no, 4)) {
		/*Create new node for tree with matched letter*/
		root->t4 = TNode_new();
		root->t4->key = table_lookup(*ph_no, 4);
		/*Add it to the tree*/
		TNode_populate(root->t4, ph_no + 1);
	}
	return root;
}

/*Prints our a four-way tree for the user.
Used for debugging purposes*/
void
TNode_print_tree(TNode *root) {
	if(root != NULL) {
		printf("%c, ", root->key);
		TNode_print_tree(root->t1);
		TNode_print_tree(root->t2);
		TNode_print_tree(root->t3);
		printf("\n");
	}
}

/*Return whether "word" can be found in the four way tree
representing a phone number given by 'root' (starting at root) */
int
TNode_word_begins(TNode *root, char *word) {

	/*If word is empty (ie end of string) then we say we CAN find word*/
	if (word[0] == '\0') 
		return TRUE;

	/*If tree is empty, then we say we CAN'T find word*/
	if (root == NULL)
		return FALSE;

	/*Otherwise, we can find word if we match on the first letter
	with the root node AND at least one of the children returns
	true for the recursive call with the remainder of the word
	minus the first letter*/
	if((root->key == tolower(word[0])) && 
		(TNode_word_begins(root->t4, word + 1) ||
		 TNode_word_begins(root->t3, word + 1) || 
		 TNode_word_begins(root->t2, word + 1) ||
		 TNode_word_begins(root->t1, word + 1))) {
		return TRUE;
	}
	/*Otherwise, we can't find the word.*/
	return FALSE;
}	

