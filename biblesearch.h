#ifndef BIBLESEARCH_H
#define BIBLESEARCH_H

#define MAX_HITS 100000
#define MAX_WORD 128
#define MAX_RESULT 1000

int bsearch_getVerse(char buffer[], int line);
int bsearch_get(char **words, int length, int result[]);

#endif
