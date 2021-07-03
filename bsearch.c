// TODO:
// error system
// bsearch? biblesearch?

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <biblec/biblec.h>

#include "bsearch.h"

// Get verse from line number in BibleC file
int bsearch_getVerse(char buffer[], int line, struct BiblecTranslation *translation) {
	int result = 0;

	// Locate book
	int book = 0;
	while (translation->books[book].start <= line) {
		book++;

		// Assume overflow means last book
		if (book > MAX_BOOKS - 1) {
			break;
		}
	}

	book--;
	
	result = translation->books[book].start;

	// Get right under last chapter
	int chapter = 0;
	while (result <= line) {
		if (chapter > translation->books[book].length) {
			return -2;
		}

		result += translation->books[book].chapters[chapter];
		chapter++;
	}
	
	result -= translation->books[book].chapters[chapter - 1];
	line -= result;

	// (verses start at zero)
	line++;

	// TODO: return as a structure instead of a
	// possible useless string
	sprintf(buffer, "%s %d %d", translation->books[book].name, chapter, line);
	return 0;
}

int getHits(int hits[], char string[], struct BiblecTranslation *translation) {
	int hit = 0;
	int line = 0;
	
	FILE *verseFile = fopen(translation->location, "r");
	if (verseFile == NULL) {
		free(hits);
		return -1;
	}

	char word[BSEARCH_MAX_WORD];
	char buffer[VERSE_LENGTH];

	while (fgets(buffer, VERSE_LENGTH, verseFile) != NULL) {
		int wc = 0;
		for (int c = 0; buffer[c] != '\0'; c++) {			
			// Make sure this is an alphabetical character
			if (buffer[c] >= 'a' && buffer[c] <= 'z') {
				word[wc] = buffer[c];
				wc++;
			} else if (buffer[c] >= 'A' && buffer[c] <= 'Z') {
				// Make character lowercase
				word[wc] = buffer[c] + ('a' - 'A');
				wc++;
			} else if (buffer[c] == ' ' || buffer[c] == '\n') {
				// Quit if no useful data was read
				if (wc <= BSEARCH_MIN_WORD) {
					word[wc] = '\0';
					wc = 0;
					continue;
				}
				
				// Reset once we encounter new line
				word[wc] = '\0';
				wc = 0;

				// Check current search word after parsing
				// current word from file
				if (!strcmp(string, word)) {
					hits[hit] = line;
					hit++;

					if (hit > BSEARCH_MAX_HITS) {
						free(hits);
						fclose(verseFile);
						return -1;
					}

					// Break loop since new
					// matches are unecessary
					break;
				}
			}
		}
		
		line++;
	}

	fclose(verseFile);
	return hit;
}

int bsearch_open(char words[][BSEARCH_MAX_WORD], int length, int result[],
		struct BiblecTranslation *translation) {
	int hit1 = getHits(result, words[0], translation);
	if (hit1 == -1) {
		return -1;
	}

	if (length == 1) {
		return hit1;
	}

	int m = 0;
	for (int w = 1; w < length; w++) {
		if (strlen(words[w]) <= BSEARCH_MIN_WORD) {
			continue;
		}
		
		int *hits2 = malloc(BSEARCH_MAX_HITS);
		int hit2 = getHits(hits2, words[w], translation);
		if (hit2 == -1) {
			free(hits2);
			return -1;
		}

		// Match last word with current word
		m = 0;
		int *temp = malloc(BSEARCH_MAX_HITS);
		for (int x = 0; x < hit1; x++) {
			for (int y = 0; y < hit2; y++) {
				if (result[x] == hits2[y]) {
					temp[m] = result[x];
					m++;

					// Max results reached, don't quit, but
					// kill matching silently
					if (m > BSEARCH_MAX_HITS) {
						free(hits2);
						free(temp);
						return m;
					}
				}
			}
		}

		// Copy for matching next
		memcpy(result, temp, sizeof(int) * m);

		free(hits2);
		free(temp);
	}

	return m;
}
