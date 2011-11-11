/*Given a number "no", return TRUE if this number
corresponds to "letter" on a touch phone dial pad.
FALSE otherwise.*/
int number_matches_letter(char no, char letter);

/*Returns the nth possible letter associated with
the digit represented by lookupchar.  Returns \0 if
no nth possible letter is associated with that digit.
Eg table_lookup('2', 1) == a*/
char table_lookup(char lookupchar, int n);
