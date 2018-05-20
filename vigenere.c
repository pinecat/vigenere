#include "vigenere.h"

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

	switch(input) {
		case 1: {
			printf("Enter plaintext: ");
			read_line(text);
			printf("Enter key: ");
			read_line(key);
			encrypt(text, key);
			printf("Ciphertext: %s\n", text);
		} break;
		
		case 2: {
			printf("Enter ciphertext: ");
			read_line(text);
			printf("Enter key: ");
			read_line(key);
			decrypt(text, key);
			printf("Plaintext: %s\n", text);
		} break;

		default: {
			printf("Invalid option!\n");
			exit(1);
		} break;
	}

	return 0;
}

void encrypt(char *text, char *key)
{
	char *newkey = refine_key(key, get_strlength(text));
	int i, j;
	i = j = 0;
	while (text[i] != '\0') {
		char c = text[i];
		if (is_letter(c)) { // c is a letter
			if (is_lower(c)) { // c is lower case
				c = (c + to_lower(newkey[j]) - 2 * 'a') % 26 + 'a';
			} else { // c is upper case
				c = (c + to_upper(newkey[j]) - 2 * 'A') % 26 + 'A';
			}
			text[i] = c;
			j++;
		}
		i++;
	}
}

void decrypt(char *text, char *key)
{
	// (c - newkey[j] + 26) % 26 + 'a';
	char *newkey = refine_key(key, get_strlength(text));
	int i, j;
	i = j = 0;
	while (text[i] != '\0') {
		char c = text[i];
		if (is_letter(c)) { // c is a letter
			if (is_lower(c)) { // c is lower case
				c = (c - to_lower(newkey[j]) + 26) % 26 + 'a';
			} else { // c is upper case
				c = (c - to_upper(newkey[j]) + 26) % 26 + 'A';
			}
			text[i] = c;
			j++;
		}
		i++;
	}
}

char *refine_key(char *key, int textlength)
{
	char *newkey = (char *)(malloc(sizeof(char) * STR_LEN));
	int i, j;
	i = j = 0;
	while ( i != textlength) {
		if (is_letter(key[j])) {
			newkey[i] = key[j];
			i++;
		}
		j++;
		if (key[j] == '\0') {
			j = 0;
		}
	}
	newkey[textlength] = '\0';
	return newkey;
}

int get_strlength(char *text)
{
	int i = 0;
	while (text[i++] != '\0');
	return (i - 1);
}

int is_letter(char c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')) return 1;
	return 0;
}

char to_upper(char c)
{
	if (is_lower(c)) c = c - 'a' + 'A';
	return c;
}

char to_lower(char c)
{
	if (is_upper(c)) c = c - 'A' + 'a';
	return c;
}

int is_upper(char c)
{
	if (c >= 'A' && c <= 'Z') return 1;
	return 0;
}

int is_lower(char c)
{
	if (c >= 'a' && c <= 'z') return 1;
	return 0;
}

void read_line(char *text)
{
	int i = 0;
	while ((text[i++] = getchar()) != '\n');
	text[i - 1] = '\0';
}
