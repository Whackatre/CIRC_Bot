/*
 utils.c
 @author justin zeng (whackatre)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "utils.h"

#define STREQ_CMP 1024

char char_template[] =
{
	'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j',
	'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't',
	'u', 'v', 'w', 'x', 'y', 'z', 'A', 'B', 'C', 'D',
	'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N',
	'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
	'Y', 'Z', '0', '1', '2', '3', '4', '5', '6', '7',
	'8', '9'
};


int rand_int(const int min, const int max)
{
	static int init = 0;
	int rc;
	if (init == 0)
	{
		srand(time(NULL));
		init = 1;
	}
	rc = (rand() % (max - min + 1) + min);
	return rc;
}

int streq(char* s1, const char* s2)
{
	return strncmp(s1, s2, STREQ_CMP) == 0;
}

char* rand_str(int len)
{
	int i;
	char* gen = (char*) malloc(len + 1);
	for (i = 0; i < len; i++)
	{
		gen[i] = char_template[rand_int(
			0, sizeof(char_template) / sizeof(*char_template))];
	}
	gen[len] = '\0';
	return gen;
}

char** str_split(const char* string, const char* const delimiter, size_t* count)
{
	const size_t stringLength = strlen(string);
	const size_t delimiterLength = strlen(delimiter);
	const char* i;
	char** split = (char**) malloc((stringLength + 1) * sizeof(char*));
	*count = 0;

	for (i = 0; (i = strstr(string, delimiter)) != 0; string = i + delimiterLength)
	{
		const size_t length = i - string;
		split[*count] = (char*) calloc(length + 1, sizeof(char));
		strncpy(split[*count], string, length);
		++*count;
	}

	split[*count] = (char*) calloc(strlen(string) + 1, sizeof(char));
	strcpy(split[*count], string);
	++*count;
	split = (char**) realloc(split, *count * sizeof(char*));

	return split;
}

char char_at(char* str, unsigned int idx)
{
	unsigned int i, len;
	len = strlen(str);
	if (idx > len)
		return '\0';
	return str[idx];
}

int idx_of(char* str, char c)
{
	unsigned int i, len;
	len = strlen(str);
	for (i = 0; i < len; i++)
		if (str[i] == c)
			return i;
	return -1;
}