#ifndef BIBLESEARCH_H
#define BIBLESEARCH_H

#define MAX_HITS 100000
#define MAX_WORD 128
#define MAX_RESULT 1000
#define MIN_WORD 2

int bsearch_getVerse(char buffer[], int line,
		struct Biblec_translation *translation);

int bsearch_open(char **words, int length, int result[],
		struct Biblec_translation *translation);

#endif
