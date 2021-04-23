#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "biblec/main.h"

struct Search {
	char *word[20];
	int hits[20];
	int wordsLength;
};

struct Search mySearch = {
	{"for", "god", "so", "loved"},
	{0, 0, 0, 0},
	4
};

int findWords(struct Search *search, char *word) {
	for (int w = 0; w < search->wordsLength; w++) {
		if (!strcmp(search->word[w], word)) {
			search->hits[w]++;
		}
	}
}

int main() {
	struct Biblec_translation translation;
	int tryFile = biblec_parse(
		&translation,
		"biblec/bibles/kj2000.i"
	);

	if (tryFile) {
		puts("Index parsing error");
		return 0;
	}

	FILE *verseFile = fopen(translation.location, "r");
	if (verseFile == NULL) {
		puts("err");
		return -1;
	}

	char word[50];
	int wordC = 0;

	char buffer[VERSE_LENGTH];
	while (fgets(buffer, VERSE_LENGTH, verseFile) != 0) {
		for (int c = 0; buffer[c] != '\0'; c++) {
			// Make sure this is an alphabetical character
			if (buffer[c] >= 'a' && buffer[c] <= 'z') {
				word[wordC] = buffer[c];
				wordC++;
			} else if (buffer[c] >= 'A' && buffer[c] <= 'Z') {
				word[wordC] = buffer[c] + ('a' - 'A'); // Make character lowercase
				wordC++;
			} else if (buffer[c] == ' ' || buffer[c] == '-') {
				// Reset once we encounter new line
				word[wordC] = '\0';
				wordC = 0;

				findWords(&mySearch, word);
			}
		}
 	}

	for (int i = 0; i < mySearch.wordsLength; i++) {
		printf("%d ", mySearch.hits[i]);
	}

	fclose(verseFile);
}

/*
Hits:
John 3 16  for, god, so, loved
Heb 4 12   for, god, so




*/
