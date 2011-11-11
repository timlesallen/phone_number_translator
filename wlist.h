/*Data structure for representing the results of
probing a phone number.
It is a simple link list of words and the position
at which that word was found.*/
typedef struct _WList_node WList_node;
struct _WList_node {
	char word[32];
	int pos;
	WList_node *next;
};

/*Create the word list*/
WList_node *WList_create(TNode *root, FILE *dictfile); 

/*Print the word list so the user can see results*/
void WList_print(WList_node *list);

/*Build the word list (basically this the guts of
the probing algorithm*/
WList_node* WList_build(DTNode *root, char *ph_no);
