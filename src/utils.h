/*
 utils.h
 @author justin zeng (whackatre)
 */

#include <stdlib.h>

char char_template[62];

/*
 generates a random integer.
 */
int rand_int(const int min, const int max);

/*
 string equality (by t4).
 */
int streq(char* s1, const char* s2);

char* rand_str(int len);
