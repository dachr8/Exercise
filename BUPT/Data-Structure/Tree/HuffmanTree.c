#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


// Huffman tree storage representation
typedef struct HTNode {
	int weight;                 // Node weight
	int parent, lchild, rchild; // The subscripts of the parents, left child, and right child of the node
}HTNode, *HuffmanTree;

// Huffman code table storage representation
typedef char **HuffmanCode;     // Dynamically allocated array storage Huffman code table


// Construct Huffman Tree HT
void createHuffmanTree(HuffmanTree *HT, int n) {
	if (n <= 1)
		return;
	int m = 2 * n - 1;
	*HT = malloc(sizeof(HTNode)*(m + 1)); // Unit 0 is unused, so it is necessary to dynamically allocate m+1 units, and HT[m] represents the root node.
	if (!*HT)
		exit(1);

	for (int i = 1; i <= m; ++i)          // Initialize the subscripts of the parents, left child, and right child in the 1~m unit to 0.
		HT[i]->parent = HT[i]->lchild = HT[i]->rchild = 0;
	for (int i = 1; i <= n; ++i)          // Enter the weight of the leaf node in the first n units
		scanf("%d",HT[i]->weight);

	// At the end of the initialization work, the following begins to create the Huffman tree.

	for (int i = 1; i <= m; ++i) {                       // Create a Huffman tree by n-1 selections, deletions, and merges
		select(*HT, i - 1, s1, s2);                      // Select two nodes whose parent domain is 0 and whose weight is the smallest among HT[k](1<=k<=i-1), and return their sequence numbers s1 and s2 in HT.
		HT[s1]->parent = HT[s2]->parent = i;             // Get the new node i, remove s1 and s2 from the forest, change the parental domain of s1 and s2 from 0 to i
		HT[i]->lchild = s1;                              // s1 as the left child of i
		HT[i]->rchild = s2;                              // s2 as the right child of i
		HT[i]->weight = HT[s1]->weight + HT[s2]->weight; // The weight of i is the sum of the weights of the left and right children.
	}
}


// Reverse the Huffman code for each character from the leaf to the root and store it in the code table HC
void createHuffmanCode(HuffmanTree HT, HuffmanCode *HC, int n) {
	*HC = malloc(sizeof(char*)*(n + 1));          // Allocate a code table space that stores n character encodings
	if (!*HC)
		exit(1);

	char *cd = malloc(sizeof(char)*(n));          // Allocate a dynamic array space that temporarily stores each character encoding
	if (!cd)
		exit(1);

	cd[n - 1] = '\0';                             // Code terminator
	for (int i = 1; i <= n; ++i) {                // Calculate Huffman coding character by character
		int start = n - 1;                        // Start points from the beginning to the end, that is, the encoding end position
		int c = i;
		int f = HT[i].parent;                     // f points to the parent node of node c
		while (f) {                               // Back up from the leaf node until the root node
			--start;                              // Backtracking once forward refers to a position
			cd[start] = (HT->lchild == c)?'0':'1';
			c = f;
			f = HT[f].parent;                     // Continue to go back
		}
		HT[i] = malloc(sizeof(char)*(n - start)); // Allocate space for the i-th character encoding
		strcpy(*HC[i], *cd[start]);               // Copy the obtained code from the temporary space cd to the current line of the HC
	}
	free(cd);                                     // Release temporary space
}