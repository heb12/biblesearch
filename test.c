#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <biblec/main.h>

#include "bsearch.h"

struct Biblec_translation translation;

int main() {
	int tryFile = biblec_parse(
		&translation,
		"/home/dan/.local/share/heb12/web.i"
	);

	if (tryFile) {
		return -1;
	}

	char *mySearch[] = {
		"created",
		"beginning"
	};

	int *result = malloc(MAX_HITS);
	int c = bsearch_open(
		mySearch,
		sizeof(mySearch) / sizeof(mySearch[0]),
		result,
		&translation
	);

	printf("Result: %d\n", c);

	if (c == -1) {
		return -1;
	}

	char buffer[128];
	for (int i = 0; i < c; i++) {
		bsearch_getVerse(buffer, result[i], &translation);
		printf("%d\t%s\n", result[i], buffer);
	}

	free(result);

	puts("bsearch_getVerse bugs:");
	bsearch_getVerse(buffer, 30650, &translation);
	puts(buffer);
	bsearch_getVerse(buffer, 31093, &translation);
	puts(buffer);

	return 0;
}
