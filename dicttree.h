/*Data structure and functions relating to a tree for holding the 
dictionary words in a data structure that is quickly searchable*/
typedef struct _DTNode DTNode;

struct _DTNode {
	char key; /*Character at this node*/
	int end_of_word; /*Whether a word ends here (TRUE or FALSE)*/
	DTNode *child;
	DTNode *sibling;
};

DTNode* DTNode_new(char key);
DTNode* DTree_word_insert(DTNode *root, DTNode *curr_child, char *word);
DTNode* DTree_build(FILE *dictfile);
void DTree_print(DTNode *root);

	
