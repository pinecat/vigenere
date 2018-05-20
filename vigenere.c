/**************************************************************
*
*	Project Name:	vigenere
*	Description:	implementation of a vigenere cipher in c
*	Filenames:		vigenere.c vigenere.h
*	Author:			rory
*
**************************************************************/

/* imports */
#include "vigenere.h"

/*
	main:		main function of the program

	params:		none

	returns:	0 - clean exit
				1 - something went wrong
*/
int main()
{
	char text[STR_LEN]; // string to hold plaintext/ciphertext from user
	char key[STR_LEN]; // string to hold key from user
	int input; // used to store user input for main menu

	memset(text, 0, sizeof(text)); // set text to all 0's at first, since it is a string
	memset(key, 0, sizeof(key)); // set key to all 0's at first, since it is a string

	// print logo
	printf("   ._  _  _  _  __ \n");
	printf("|///_//_'/ //_'//_'\n");
	printf("   _/ by aschen  \n\n");

	// print menu
	printf("1. Encrypt\n2. Decrypt\n\nEnter option: ");
	scanf("%d", &input); // get input from user
	getchar(); // input formating

	switch(input) { // switch on user input from main menu
		case 1: { // user entered "1" (encrypt)
			printf("Enter plaintext: "); // ask user for plaintext
			read_line(text); // read in user plaintext
			printf("Enter key: "); // ask user for key
			read_line(key); // read in user key
			encrypt(text, key); // encrypt the text with the key
			printf("Ciphertext: %s\n", text); // print the ciphertext to the user
		} break;
		
		case 2: { // user entered "2" (decrypt)
			printf("Enter ciphertext: "); // ask user for ciphertext
			read_line(text); // read in user ciphertext
			printf("Enter key: "); // ask user for key
			read_line(key); // read in user key
			decrypt(text, key); // decrypt the text with the key
			printf("Plaintext: %s\n", text); // print the plaintext to the user
		} break;

		default: { // user entered an invalid option
			printf("Invalid option!\n"); // print message to user
			exit(1); // exit with error
		} break;
	}

	return 0; // clean exit
}

/*
	encrypt:	takes in two strings, a text, and a key, and performs a vigenere cipher on the text to encrypt it via the key

	params:		*text - the string to be encrypted
				*key - the key to encrypt the text with

	returns:	void
*/
void encrypt(char *text, char *key)
{
	char *newkey = refine_key(key, get_strlength(text)); // refine the key (remove anything that isn't a letter, and extend the key so it's length is the same as the text)
	int i, j; // indexes (i for text, j for newkey)
	i = j = 0; // set indexes to 0 initially
	while (text[i] != '\0') { // loop through until we reach the end of the text string
		char c = text[i]; // used so i don't have to keep typing text[i]
		if (is_letter(c)) { // c is a letter (if c is a letter, we want to shift it, otherwise just ignore it)
			if (is_lower(c)) { // c is lowercase
				c = (c + to_lower(newkey[j]) - 2 * 'a') % 26 + 'a'; // perform appropriate shift on c if it is lowercase
			} else { // c is uppercase
				c = (c + to_upper(newkey[j]) - 2 * 'A') % 26 + 'A'; // perform appropriate shift on c if it is uppercase
			}
			text[i] = c; // set text[i] to the shifted c
			j++; // increment j (index for newkey)
		}
		i++; // increment i (index for text) (this will happen regardless of whether or not c gets shifted)
	}
}

/*
	decrypt:	takes in two strings, a text, and a key, and performs a vigenere cipher on the text to decrypt it via the key

	params:		*text - the string to be decrypted
				*key - the key to decrypt the text with

	returns:	void
*/
void decrypt(char *text, char *key)
{
	char *newkey = refine_key(key, get_strlength(text)); // refine the key (remove anything that isn't a letter, and extend the key so it's length is the same as the text)
	int i, j; // indexes (i for text, j for newkey)
	i = j = 0; // set indexes to 0 initally
	while (text[i] != '\0') { // loop through until we reach the end of the text string
		char c = text[i]; // used so i don't have to keep typing text[i]
		if (is_letter(c)) { // c is a letter
			if (is_lower(c)) { // c is lowercase
				c = (c - to_lower(newkey[j]) + 26) % 26 + 'a'; // perform appropriate shift on c if it is lowercase
			} else { // c is uppercase
				c = (c - to_upper(newkey[j]) + 26) % 26 + 'A'; // perform appropriate shift on c if it is uppercase
			}
			text[i] = c; // set text[i] to the shifted c
			j++; // increment j (index for newkey)
		}
		i++; // increment i (index for text) (this will happen regardless of whether or not c gets shifted)
	}
}

/*
	refine_key:	takes in the original key string and refines it so that it will be the same length as the text being encrypted/decrypted and it contains only letters
	
	params:		*key - the original key string, it will be refined
				textlength - the length of the text to be encrypted/decrypted (not the key's length)

	returns:	newkey - the refined key (only letters, and extended to be the same length as the text to be encrypted/decrypted)
*/
char *refine_key(char *key, int textlength)
{
	char *newkey = (char *)(malloc(sizeof(char) * STR_LEN)); // malloc a char array with STR_LEN number of indexes
	int i, j; // indexes (i for newkey/textlength, j for key)
	i = j = 0; // set indexes to 0 initially
	while ( i != textlength) { // loop through while i is less than textlength (note: not the length of the key, but the length of the text being encrypted or decrypted)
		if (is_letter(key[j])) { // if key[j] is a letter....
			newkey[i] = key[j]; // set newkey[i] to whatever key[j] is
			i++; // increment i (only increment this if a letter from key is placed into newkey)
		}
		j++; // increment j (always do this)
		if (key[j] == '\0') { // if j == the NULL character, in otherwords, if we reach the end of the keystring....
			j = 0; // reset j to 0
		}
	}
	newkey[textlength] = '\0'; // NULL terminate newkey at the appropriate place, as it is a string
	return newkey; // return newkey
}

/*
	get_strlength:	returns the length of a NULL terminated string

	params:			*text - the text to get the string length from

	returns:		the length of the text (example string: "hello" will return 5 (so long as it is properly NULL terminated))
*/	
int get_strlength(char *text)
{
	int i = 0; // index / counter
	while (text[i++] != '\0'); // increment i while we have not reached the end of the text passed in
	return (i - 1); // return i - 1 (i gets incremented one too many times, so subtract 1 before returning) (example string: "hello" will return 5)
}

/*
	to_upper:	takes a character, and if it is lowercase, will make it uppercase

	params:		c - the character to be made uppercase

	returns:	c - returns the uppercase character (if c was not lowerase to begin with, just returns the original value of c)
*/
char to_upper(char c)
{
	if (is_lower(c)) c = c - 'a' + 'A'; // if c is lowercase, make c uppercase
	return c; // return c (returns the character unchanged if it was not lowercase)
}

/*
	to_lower:	takes a character, and if it is uppercase, will make it lowercase

	params:		c - the characterto be made lowercase

	returns:	c - returns the lowercase character (if c was not uppercase to begin with, just returns the original value of c)
*/
char to_lower(char c)
{
	if (is_upper(c)) c = c - 'A' + 'a'; // if c is uppercase, make c lowercase
	return c; // return c (returns the character unchagned if it was not uppercase)
}

/*
	is_upper:	determines whether or not a character is uppsercase

	params:		c - the character to make the determination on

	returns:	1 (true) - if c is an uppercase letter
				0 (false) - if c is not an uppercase letter
*/
int is_upper(char c)
{
	if (c >= 'A' && c <= 'Z') return 1; // if c falls between uppercase A and Z (in otherwords, c is an uppercase letter), return 1 (true)
	return 0; // otherwise return 0 (false)
}

/*
	is_lower:	determines whether or not a character is lowercase

	params:		c - the character to make the determination on

	returns:	1 (true) - if c is a lowercase letter
				0 (false) - if c is not a lowercase letter
*/
int is_lower(char c)
{
	if (c >= 'a' && c <= 'z') return 1; // if c falls between lowercase a and z (in otherworse, c is a lowercase eltter), return 1 (true)
	return 0; // otherwise return 0 (false)
}

/*
    is_letter:  determines whether or not a character is a letter

    params:     c - the character to see whether or not it is a letter

    returns:    1 (true) - if c is a letter
                0 (false) - if c is not a letter
*/
int is_letter(char c)
{
    if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')) return 1; // if c falls between uppercase A and Z or lowercase a and z, return 1 (true)
    return 0; // otherwise return 0 (false)
}

/*
	read_line:	reads input from stdin, but is newline deliminated, unlike scanf which is space deliminated

	params:		*text - the text you want to read the input into

	returns:	void
*/
void read_line(char *text)
{
	int i = 0; // index, start it at 0
	while ((text[i++] = getchar()) != '\n'); // get characters until we hit a newline (newline deliminated) and store it into text, remembering to increment i
	text[i - 1] = '\0'; // NULL terminate text at i - 1, as it will overwrite the newline character at that position
}
