#define TRUE 1
#define FALSE 0

char
table_lookup(char lookup, int no) {

	static char lookup_table[10][4] = {
		{'0','\0','\0','\0'},
		{'1','\0','\0','\0'},
		{'a','b','c','\0'},
		{'d','e','f','\0'},
		{'g','h','i','\0'},
		{'j','k','l','\0'},
		{'m','n','o','\0'},
		{'p','r','s','\0'},
		{'t','u','v','\0'},
		{'w','x','y','z'}
	};
	if (lookup == '\0') return '\0';
	return lookup_table[lookup - '0'][no - 1];
}

int number_matches_letter(char no, char letter) {
	if (letter == '\0') return FALSE;
	if (letter == table_lookup(no, 1) ||
	    letter == table_lookup(no, 2) ||
	    letter == table_lookup(no, 3) ||
	    letter == table_lookup(no, 4))
		return TRUE;
	return FALSE;
}
	

	
