#ifndef BIBLESEARCH_H
#define BIBLESEARCH_H

#define BSEARCH_MAX_HITS 100000
#define BSEARCH_MAX_WORD 128
#define BSEARCH_MIN_WORD 2

int bsearch_getVerse(char buffer[], int line,
		struct Biblec_translation *translation);

int bsearch_open(char words[][BSEARCH_MAX_WORD], int length, int result[],
		struct Biblec_translation *translation);

#endif
