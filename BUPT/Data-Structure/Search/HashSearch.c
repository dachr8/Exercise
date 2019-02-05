#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


// Open address method hash table storage representation
#define M 20
typedef char keyType;
typedef char infoType;
typedef struct {
	keyType key;   // Keyword item
	infoType info; // Other data items
}hashTable[M];


#define NULLKEY 0 // Empty mark
// Search the element whose key is key in the hash table HT.
// If the search is successful, return the unit tag of the hash table, otherwise return -1.
int searchHash(hashTable HT, keyType key) {
	int H0 = H(key);       // Calculate the hash address based on the hash function H(key)
	if (HT[H0].key == NULLKEY)
		return -1;         // If the unit H0 is empty, the checked element is unsuccessful

	if (HT[H0].key == key)
		return H0;         // If the keyword of the element in unit H0 is key, the search is successful.

	for (int i = 1; i < M; ++i) {
		Hi = (H0 + i) % m; // Calculate the next hash address Hi according to the current detection method
		if (HT[Hi].key == NULLKEY)
			return -1;     // If the unit Hi is empty, the element being checked does not exist.

		if (HT[H0].key == key)
			return Hi;     // If the keyword of the element in unit Hi is key, the search is successful.
	}
	return -1;
}