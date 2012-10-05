/*
 utils.h
 @author justin zeng (whackatre)
 */

#include <stdlib.h>
#include <string.h>

char char_template[62];

/*
 generates a random integer.
 */
int rand_int(const int min, const int max);

/*
 string equality (by t4).
 */
int streq(char* s1, const char* s2);

/*
 returns a random alphanumerical
 string with length len.
 */
char* rand_str(int len);

/*
 returns a char**.
 string: the string.
 delimiter: the delimiter.
 count: the # of strings (after function).
 
 THANKS ENFORCER!
 */
char** str_split(const char* string, const char* const delimiter, size_t* count);

/*
 returns the char of the given
 string at the given index.
 returns \0 if idx is out of range.
 */
char char_at(char* str, unsigned int idx);

/*
 returns the idx number
 of the char in the string.
 returns -1 if char does
 not exist in the string.
 */
int idx_of(char* str, char c);

/*
 joins a string.
 */
char* join(const char* s1, const char* s2);

/*
 if a string starts with
 another string.
 */
int starts_with(const char* str1, const char* str2);