#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <biblec/biblec.h>

#include "bsearch.h"

struct BiblecTranslation translation;

int main() {
	int tryFile = biblec_parse(
		&translation,
		"/home/dan/.local/share/heb12/web.i"
	);

	if (tryFile) {
		return -1;
	}

	clock_t start = clock();

	char mySearch[][BSEARCH_MAX_WORD] = {
		"created",
		"heavens",
		"earth"
	};

	int *result = malloc(BSEARCH_MAX_HITS);
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

	double elapsed = (double)(clock() - start) / CLOCKS_PER_SEC;
	printf("Done in %f seconds.\n", elapsed);

	free(result);
	return 0;
}
