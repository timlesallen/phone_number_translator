#include <stdlib.h>
#include <stdio.h>
#include "dicttree.h"
#include "dict.h"
#define FALSE 0
#define TRUE 1
#define MAX_WORD_LENGTH 32 /*Assume no word in dict is longer than 31 chars*/

/*Creates a new DTNode with given key*/
DTNode* 
DTNode_new(char key) {
	DTNode *dp;
	if ((dp = malloc(sizeof(DTNode)))) {
		dp->key = key;
		dp->child = NULL;
		dp->sibling = NULL;
			return dp;
	}
	else
		exit(EXIT_FAILURE);
}

/*Given dictionary tree represented by root, insert word into it.*/
DTNode*
DTree_word_insert(DTNode *root, DTNode *curr_child, char *word) {
	DTNode *temp = NULL;

	/*If root is NULL, then WHAT?*/
	if(root == NULL) {
#ifdef DEBUG
		printf("Root NULL\n");
#endif
		return root;
	}

	/*If we have end of string, then mark root as end of a word*/
	if(word[0] == '\0') {
		root->end_of_word = TRUE;
#ifdef DEBUG
		printf("End of word - setting end_of_word\n");
#endif
	return root;
	}
	if(root->child == NULL) {
#ifdef DEBUG
		printf("root->child NULL - inserting to child - recurring on " 
				"child\n");
#endif
		root->child = DTNode_new(word[0]);
		return DTree_word_insert(root->child, 
				root->child->child, word + 1);
	}

	/* If current child matches first letter of word, then recurse on curr_child*/
	if(curr_child->key == word[0]) {
#ifdef DEBUG
		printf("curr_child->key (%c) matches, recurring on child\n"
				, curr_child->key);
#endif
		return DTree_word_insert(curr_child, 
				curr_child->child, word + 1);
	}

	/*Else if we made it here and sibling is NULL, then we need to insert a sibling
        with the first letter of word as the key*/
	if(curr_child->sibling == NULL) {
#ifdef DEBUG
		printf("curr_child->sibling NULL - inserting to sibling\n");
#endif
		curr_child->sibling = DTNode_new(word[0]);
		return DTree_word_insert(curr_child->sibling, 
				curr_child->sibling->child, word + 1);
	}
	/*Otherwise if we get here we do have a sibling
	If it is lexographically greater than first letter of word, we need to insert
        first letter of word before it*/
	if (curr_child->sibling->key > word[0]) {
#ifdef DEBUG
		printf("Insertion happened\n");
#endif
		temp = curr_child->sibling;
		curr_child->sibling = DTNode_new(word[0]);
		curr_child->sibling->sibling = temp;
		return DTree_word_insert(curr_child->sibling, 
				curr_child->sibling->child, word + 1);
	}
#ifdef DEBUG
	printf("Moving to sibling (%c)....\n", curr_child->sibling->key);
#endif
	/*Otherwise, we do have a sibling and we don't need to insert before it,
	so we just recurse to it.*/
	return DTree_word_insert(root, curr_child->sibling, word);
}

/*Generate tree that represents all word in dictionary.
Root node does not correspond to a letter but has key '\0'
*/
DTNode*
DTree_build(FILE *dictfile) {
	char word[MAX_WORD_LENGTH]; /*The current word*/
	DTNode *root; /*Pointer to root of dictionary tree*/
	int i = 0;
	
	
	root = DTNode_new('\0');

	/*For each word in the dictionary*/		
	while(dictfile_word_next(word, dictfile) ) {
#ifdef DEBUG
	       printf("WORD: %s\n", word);	
#endif
		/*Insert word into dictionary tree*/
		DTree_word_insert(root, root->child, word);
		i++;
	}
	return root; /*Return pointer to root of tree*/
}

/*Function to print out dictionary tree (used for debugging)*/
void
DTree_print(DTNode *root) {
	if(root == NULL)
		return;
	printf("%c",root->key);
	DTree_print(root->sibling);
	printf("\n");
	DTree_print(root->child);
}
