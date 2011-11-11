#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "dict.h"
#include "tree.h"
#include "dicttree.h"
#include "wlist.h"
#include "table.h"
#define FALSE 0
#define TRUE 1

/*Local function prototypes*/
WList_node *WList_node_new(void);
WList_node *WList_node_add(WList_node *list, WList_node *newn);

/*new stuff (dicttree algorithm)*/
WList_node *WList_generate(DTNode *root, WList_node *wl, char *ch_sofar, 
		int depth, int depth_offset, char *ph_no);
WList_node *WList_insert(WList_node *wl, char *word, int pos); 

/*Given a dictionary tree and a phone number for probing,
return the list of words found*/
WList_node*
WList_build(DTNode *root, char *ph_no) {

	WList_node *wl = NULL; /*Word list we will return*/
	char ch_sofar[64];
	int depth_offset = 0;
	
	/*For each substring given by starting with the entire number
	and shaving off the first letter each iteration, find all words
	that match against substring, and add them to word list*/
	for(; strlen(ph_no) > 0; ph_no++, depth_offset++)
		wl = WList_generate(root, wl, ch_sofar, 0, depth_offset, ph_no);

	return wl;
}

/*Given a string 'word' and a position at which it was found,
insert a new entry in word list "wl" that represents
that word and position*/
WList_node*
WList_insert(WList_node *wl, char *word, int pos) {
	WList_node *newn;
	
	newn = WList_node_new();
	strcpy(newn->word, word);
	newn->pos = pos;
	wl = WList_node_add(wl, newn);
	return wl;
}
/*

Given a substring representing all or part of a phone number (ph_no)
find all words that are to be found that start at the start of that
number and continue to subsequent digits.  Append these words to 
the word list (wl).

root - the dictionary tree we are searching against

wl - a word list to append to

ch_sofar - Prefix of all words represented by this node in the tree

depth - How deep we are in the dictionary tree

depth_offset - How many letters we have chopped off the phone number
under consideration

ph_no - The portion of the phone number (possibly less a prefix wrt 
the original number) currently being analysed

*/
WList_node*
WList_generate(DTNode *root, WList_node *wl, char *ch_sofar, 
		int depth, int depth_offset, char* ph_no) {
	/*If dictionary tree is empty then we can't do anything more*/
	if (root == NULL)
		return wl;

	/*If we are not at the top level, append key of current root node
	to ch_so_far*/
	if (depth > 0 ) {
		ch_sofar[depth - 1] = root->key;
		ch_sofar[depth] = '\0';
	}	

	/*If root of tree is the end of a word, and the digit we are considering
	associates to the letter at root, then we found a word!*/
	if (root->end_of_word == TRUE && number_matches_letter(ph_no[depth - 1], 			tolower(root->key)))
		/*Add word we found to word list*/
		wl = WList_insert(wl, ch_sofar, depth_offset);

	/*If we are at the first node in the tree (should be only node
	with \0) OR root node matches digit currently being considered*/
	if ( root->key == '\0' || 
			number_matches_letter(ph_no[depth - 1], 
						tolower(root->key)))

		/*Then keep going to child of this node - we are part
		way through a word (or at root of dictionary tree).*/
		wl = WList_generate(root->child, wl, ch_sofar, 
					depth + 1, depth_offset, ph_no);

	/*As this is a depth first search (and we have already
	dealt with recursion on the child above), we are now ready to traverse
	to the sibling, so blot out the letter in ch_sofar obtained
	at the current node, and recurse to the sibling*/
	if (depth > 0)
		ch_sofar[depth - 1] = '\0';
	wl = WList_generate(root->sibling, wl, ch_sofar, 
				depth, depth_offset, ph_no);
	
	return wl;
}	

/*Create new node for word list*/
WList_node*
WList_node_new(void) {
	WList_node *wp;
	if((wp = (WList_node*) malloc(sizeof(WList_node))) != NULL) {
		wp->next = NULL;
		return wp;
	}
	fprintf(stderr, "Error allocating memory. Terminating.\n");
	exit(EXIT_FAILURE);
}

/*Add new node to word list*/
WList_node*
WList_node_add(WList_node *list, WList_node *newn) {
	if (list == NULL)
		return newn;
	if (list->next == NULL) {
		list->next = newn;
		return list;
	}
	else {
		WList_node_add(list->next, newn);
		return list;
	}
}

/*Given a dictionary file and a four way tree reprenting the permutations
available in a phone number, generate the word list of words found

NB: This is no longer used.  It is part of the older less efficient
algorithm.*/
WList_node*
WList_create(TNode *root, FILE *dictfile) {
	char word[32];
	TNode *cn;
	int pos;
	int found;
	WList_node *list = NULL;
	WList_node *newn;
	
 	/*For each word in the dictionary*/	
	while(dictfile_word_next(word, dictfile)){
			
		
		for(cn = root, pos = 0, found = FALSE; 
				cn != NULL; cn = cn->t3, pos++) {
			if (TNode_word_begins(cn->t4, word) ||
			    TNode_word_begins(cn->t3, word) ||
			    TNode_word_begins(cn->t2, word) ||
			    TNode_word_begins(cn->t1, word)) {
				found = TRUE;
			}
		
			if(found == TRUE) {
				newn = WList_node_new();
				strcpy(newn->word, word);
				newn->pos = pos;
				list = WList_node_add(list, newn);
				found = FALSE;
			}
		}
	}
	return list;	
}

/*Print out word list to user.  Used to show
user the words found in a number.*/
void
WList_print(WList_node *list) {
	if(list == NULL)
	       return;
	if(list->next == NULL) {
		printf("%s at (%d)\n", list->word, list->pos);
		return;
	}
	printf("%s at (%d)\n", list->word, list->pos);
	WList_print(list->next);
	return;
}	

