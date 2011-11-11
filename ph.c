/*Phone number translator - a program to "look for words" in your phone number
* (c) Tim Allen 2001
* 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option) 
 * any later version.
 *  
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of 
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  
 * GNU General Public License for more details.
 *  
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  
 * 02111-1307, USA.
 */

#include<stdio.h>
#include<math.h>
#include<string.h>
#include "dict.h"
#include "dicttree.h"
#include "tree.h"
#include "wlist.h"

#define TRUE 1
#define FALSE 0
#define PHNO_SIZE_MAX "100"

/*Function prototypes*/
static char *interrogate_user(char *ph_no);

/*Prints a welcome message and reads user input (phone number)
from console*/
static char* 
interrogate_user(char *ph_no) {
	printf("\n \nWelcome to the PHONE NUMBER TRANSLATOR 1.1\n");
	printf("(c) 2001 Tim Allen.\n");
	printf("Please enter the phone number you wish to probe: ");
	scanf("%" PHNO_SIZE_MAX "s", ph_no);
	printf("\n");
	
	return ph_no;
}

int 
main(void) {
	char ph_no[101]; /*Array to hold the phone number for processing*/
	DTNode *root;    /*The dictionary tree*/
	WList_node *words; /*The list of words located in the number*/
	FILE *dictfile; /*FILE pointer to dictionary file*/
	
	/*Get phone number for processing*/
	interrogate_user(ph_no);

	/*Open dictionary*/
	dictfile = dictfile_open();
	
	/*Build dictionary tree*/
	printf("Building tree...\n");
	root = DTree_build(dictfile);

	/*Get list of possible words*/
	printf("Searching...\n");
	words = WList_build(root, ph_no);

	/*Print list of words found*/
	WList_print(words);
	printf("\n");

	/*Return success (UNIX convention)*/
	return 0;
}
