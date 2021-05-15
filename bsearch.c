// This will find duplicates in a file, sadly
// not accurate searching yet, needs to be fixed

// TODO:
// error system
// bsearch? biblesearch?


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "biblec/main.h"
#include "biblesearch.h"

struct Biblec_translation translation;

// Get verse from line number in BibleC file
// (broken)
int bsearch_getVerse(char buffer[], int line) {
	int result = 0;

	// Locate book
	int book = 0;
	while (translation.books[book].start <= line) {
		if (book >= MAX_BOOKS) {
			return -1;
		}
		
		book++;
	}

	book--;
	
	result = translation.books[book].start;

	// Get right under last chapter
	int chapter = 0;
	while (result <= line) {
		if (chapter > translation.books[book].length) {
			return -1;
		}

		result += translation.books[book].chapters[chapter];
		chapter++;
	}
	
	result -= translation.books[book].chapters[chapter - 1];
	line -= result;

	// (verses start at zero)
	line++;

	sprintf(buffer, "%s %d %d", translation.books[book].name, chapter, line);
	return 0;
}

int getHits(int hits[], char string[]) {
	int hit = 0;
	int line = 0;
	
	FILE *verseFile = fopen(translation.location, "r");
	if (verseFile == NULL) {
		free(hits);
		return -1;
	}

	char word[MAX_WORD];
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
				if (wc <= MIN_WORD) {
					word[wc] = '\0';
					//printf("%d\n", hit);
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

					if (hit > MAX_HITS) {
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

int bsearch_get(char **words, int length, int result[]) {
	int tryFile = biblec_parse(
		&translation,
		"biblec/bibles/web.i"
	);

	if (tryFile) {
		return -1;
	}
	
	int hit1 = getHits(result, words[0]);
	if (hit1 == -1) {
		return -1;
	}

	if (length == 1) {
		return hit1;
	}

	int m = 0;
	for (int w = 1; w < length; w++) {
		if (strlen(words[w]) <= MIN_WORD) {
			continue;
		}
		
		int *hits2 = malloc(MAX_HITS);
		int hit2 = getHits(hits2, words[w]);
		if (hit2 == -1) {
			free(hits2);
			return -1;
		}

		// Match last word with current word
		m = 0;
		int *temp = malloc(MAX_HITS);
		for (int x = 0; x < hit1; x++) {
			for (int y = 0; y < hit2; y++) {
				if (result[x] == hits2[y]) {
					temp[m] = result[x];
					m++;

					// Max results reached, don't quit, but
					// kill matching silently
					if (m > MAX_HITS) {
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
