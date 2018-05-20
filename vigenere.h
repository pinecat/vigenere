#ifndef VIGENERE_H
#define VIGENERE_H

/* imports */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* constants */
#define STR_LEN 8192

/* function prototypes */
void encrypt(char *text, char *key);
void decrypt(char *text, char *key);
char *refine_key(char *key, int textlength);
int get_strlength(char *text);
int is_letter(char c);
char to_upper(char c);
char to_lower(char c);
int is_upper(char c);
int is_lower(char c);
void read_line(char *text);

#endif
