#include <stdio.h>
#include "tree.h"
#include "dicttree.h"
#include "dict.h"
#include "wlist.h"

int main(void) {
	
	FILE *dictfile;
	DTNode *root;
	WList_node *wl;
	
	dictfile = dictfile_open();
	root = DTree_build(dictfile);
	wl = WList_build(root, "233233233233");
	WList_print(wl);
	return 0;

}
