/*Data structure to hold a four way tree.
Each node will contain a single character.
We choose a four way tree because the maximum number of letters that a key
on the phone key-pad can have is four.
The phone number will be populated into this tree in such a way that
the tree represents all the possible permutations of strings formed by making
a choice of letter from the letters available for each digit*/
typedef struct _TNode TNode;
struct _TNode {
	char key;
	TNode *t1;
	TNode *t2;
	TNode *t3;
	TNode *t4;
};

/*Create a new four-way tree*/
TNode *TNode_new(void);

/*Given a phone number, populate it into the tree*/
TNode *TNode_populate(TNode *root, char *ph_no);

/*Print the tree for user to see it (used for debugging)*/
void TNode_print_tree(TNode *root);

/* */
int TNode_word_begins(TNode *root, char *word);
