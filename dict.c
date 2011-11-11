#include <stdio.h>
#include "dict.h"
#include <stdlib.h>
FILE*
dictfile_open(void) {
	FILE *dp;
	
	if ((dp = fopen("words", "r")) == NULL) {
		printf("WARNING: Could not open your dictionary file.\n");
		printf("Please ensure that the dictionary file is in the same");
		printf("directory as the main program.");
		exit(EXIT_FAILURE);
	}
	return dp;
}

char*
dictfile_word_next(char *word, FILE *dictfile) {
	if(fscanf(dictfile, "%s", word) !=EOF) 
		return word;
	return NULL;
}

