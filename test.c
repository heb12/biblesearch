#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "biblesearch.h"

int main() {
	char *mySearch[] = {
		"created",
		"beginning"
	};

	int result[MAX_RESULT];
	int c = bsearch_get(
		mySearch, 
		sizeof(mySearch) / sizeof(mySearch[0]),
		result
	);

	if (c == -1) {
		return -1;
	}

	char buffer[128];
	for (int i = 0; i < c; i++) {
		bsearch_getVerse(buffer, result[i]);
		puts(buffer);
	}

	return 0;
}
