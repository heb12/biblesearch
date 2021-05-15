#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "biblesearch.h"

int main() {
	char *mySearch[] = {
		"created",
		"beginning"
	};

	int *result = malloc(MAX_HITS);
	int c = bsearch_get(
		mySearch, 
		sizeof(mySearch) / sizeof(mySearch[0]),
		result
	);

	printf("Result: %d\n", c);

	if (c == -1) {
		return -1;
	}

	char buffer[128];
	for (int i = 0; i < c; i++) {
		bsearch_getVerse(buffer, result[i]);
		printf("%d\t%s\n", result[i], buffer);
	}

	free(result);

	puts("bsearch_getVerse bugs:");
	bsearch_getVerse(buffer, 30650);
	puts(buffer);
	bsearch_getVerse(buffer, 31093);
	puts(buffer);

	return 0;
}
