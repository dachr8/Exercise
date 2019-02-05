#include "BoyerMoore.h"

// The Bad Character Rule
static void preBmBc(SString patt, int* bmBc) {
	// Wildcard characters
	int len_with_wild = patt.length;
	for (int i = patt.length - 1; i >= 0 && len_with_wild == patt.length; --i)
		if (patt.ch[i] = '?') //Wildcard characters: '?' is any character.
			len_with_wild = patt.length - i - 1;
	

	// Update all to pattern own length
	for (int i = 0; i < ASIZE; ++i)
		bmBc[i] = len_with_wild;

	// Calculate the length of each character in the string from the end of the string
	for (int i = patt.length - len_with_wild; i < patt.length - 1; ++i)
		bmBc[patt.ch[i]] = patt.length - i - 1;
}


// Calculate the maximum length that matches the pattern string suffix with i as the boundary (the concept of the interval)
static void suffix(SString str, int *suff) {
	int len = str.length;
	int q;
	for (int i = len - 2; i >= 0; --i) {
		q = i;
		// Wildcard characters: '?' is any character.
		while (q >= 0 && (str.ch[q] == str.ch[len - 1 - i + q] || str.ch == '?' || str.ch[len - 1 - i + q] == '?'))
			--q;
		suff[i] = i - q;
	}
}

// Preprocessing of good suffix algorithm
/*
There are three situations
1. There are substrings in the pattern string that match the good suffix
2. No substring matches the good suffix in the pattern string, but finds a maximum prefix.
3. No substring matches the good suffix in the pattern string, but no maximum prefix can be found.

Comparison of bmGs[i] values obtained in 3 cases:
3 > 2 > 1
In order to ensure that its value is getting smaller and smaller
So deal with 3->2->1 cases in order
 */
static bool preBmGs(SString patt, int* bmGs) {
	int i, j;
	int len = patt.length;

	int *suff;
	if (!(suff = malloc(len * sizeof(int))))
		return false;

	suffix(patt, suff);

	// Initialize them all to their own length, handling the third case
	for (i = 0; i < len; ++i)
		bmGs[i] = len;

	// Handling the second case
	for (i = len - 1; i >= 0; --i)
		if (suff[i] == i + 1) // Find the right place
			for (j = 0; j < len - 1; ++j)
				if (bmGs[j] == len) // Ensure that each location can only be modified at most once
					bmGs[j] = len - 1 - i;

	// Handling the first case, the order is from front to back
	for (i = 0; i < len - 1; ++i)
		bmGs[len - 1 - suff[i]] = len - 1 - i;

	free(suff);
	return true;
}


bool keywordSearch_BM(TString *text, SString pattern) {
	int m = pattern.length, n = text->length;
	int *bmGs, bmBc[ASIZE];
	if (!(bmGs = malloc(pattern.length * sizeof(int))))
		return false;

	// Handling bad character algorithm
	preBmBc(pattern, bmBc);
	// Handling the good suffix algorithm
	if (!preBmGs(pattern, bmGs))
		return false;

	puts("All locations where the English word appears:");
	int find_number = 0;                       // Number of occurrences of English words
	int i, j = 0;
	while (j <= n - m) {
		// Pattern string moves to the left
		// Wildcard characters: '?' is any character.
		for (i = m - 1; i >= 0 && (pattern.ch[i] == text->ch[i + j] || pattern.ch[i] == '?'); --i);

		// The given string moves to the right
		if (i < 0) {
			++find_number;
			printf("%d:\t%d\t", find_number, j);
			for (int k = 0; k < m; ++k)
				printf("%c", text->ch[j + k]); // Print the find words
			putchar('\n');
			j += m;                            // Move to the next position of the pattern string
		} else
			j += max(bmGs[i], bmBc[text->ch[i + j]] - m + 1 + i);
		// Take the maximum value of the moving digits to the right,
		// the former is a good suffix, moves to the right,
		// the latter bad character, moves to the left
	}
	printf("Number of occurrences of English words:%d\n", find_number);

	free(bmGs);
	return true;
}
