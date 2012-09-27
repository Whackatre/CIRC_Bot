/*
 utils.c
 @author justin zeng (whackatre)
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "utils.h"

#define STREQ_CMP 1024

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
