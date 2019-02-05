#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAXSIZE 20          // Maximum length of the sequential list

typedef int keyType;        // Define keyword type as integer
typedef char infoType;
typedef struct redType {
	keyType key;            // Keyword item
	infoType otherinfo;     // Other data items
}redType;                   // Record type
typedef struct sqList {
	redType r[MAXSIZE + 1]; // r[0] is idle or used as a sentinel unit
	int length;             // Sequential list length
}sqList;


// Do a straight insertion sort of the sequential list L
void insertSort(sqList *L) {
	for (int i = 2; i <= L->length; ++i)
		if (L->r[i].key < L->r[i - 1].key) {                // "<", insert r[i] into the ordered subtable
			L->r[0] = L->r[i];                              // Temporarily store the record to be inserted into the watch post
			L->r[i] = L->r[i - 1];                          // r[i-1] back shift
			int j;
			for (j = i - 2; L->r[0].key < L->r[j].key; --j) // Look for the insertion position from the back to the front
				L->r[j + 1] = L->r[j];                      // The records are moved one by one until the insertion position is found
			L->r[j + 1] = L->r[0];                          // Insert r[0], the original r[i], into the correct position
		}
}


//Do a binary insertion sort of the sequential list L
void BInsertSort(sqList *L) {
	for (int i = 2; i < L->length; ++i) {
		L->r[0] = L->r[i];                      // Temporarily store the record to be inserted into the watch post
		int low = 1;                            // Set the initial low value of the interval
		int high = i - 1;                       // Set the initial high value of the interval
		while (low <= high) {                   // Binary search the inserted position in half in r[low..high]
			int m = (low + high) / 2;           // Binary
			if (L->r[0].key < L->r[m].key)
				high = m - 1;                   // Insert point in the previous child table
			else
				low = m + 1;                    // Insert point in the next child table
		}
		for (int j = i - 1; j >= high + 1; --j)
			L->r[j + 1] = L->r[i];              // Record back shift
		L->r[high + 1] = L->r[0];               // Insert r[0], the original r[i], into the correct position
	}
}


// Do a quick sort of the sequential list L by the increment dk
void ShellInsert(sqList *L, int dk) {
	for (int i = dk + 1; i <= L->length; ++i)
		if (L->r[i].key < L->r[i - dk].key) { // Need to insert r[i] into the ordered delta subtable
			L->r[0] = L->r[i];                // Temporary r[0]
			int j;
			for (j = i - dk; j > 0 && L->r[0].key < L->r[j].key; j -= dk)
				L->r[j + dk] = L->r[j];       // Record the back shift until the insertion position is found
			L->r[j + dk] = L->r[0];           // Insert r[0], the original r[i], into the correct position
		}
}

// Do a quick sort of the sequential list L by the incremental sequence dt
void ShellSort(sqList *L, int dt[], int t) {
	for (int i = 0; i < t; ++i)
		ShellInsert(L, dt[i]);
}


// Do a quick sort of the sequential list L
void bubbleSort(sqList *L) {
	int m = L->length - 1;
	bool flag = true;                  // Flag is used to mark whether a certain sort is exchanged.
	while (m > 0 && flag) {
		flag = false;                  // Flag is set to false, if there is no swap in this order, the next sort will not be performed.
		for (int i = 1; i <= m; ++i)
			if (L->r[i].key > L->r[i + 1].key) {
				flag = true;           // Flag is set to true, indicating that the ordering has been exchanged.
				redType tmp = L->r[i]; // Exchange two records before and after
				L->r[i] = L->r[i + 1];
				L->r[i + 1] = tmp;
			}
		--m;
	}
}


// Do a sort of the sublist r[low..high] of the sequential list L, and return the pivot position.
int partition(sqList *L, int low, int high) {
	L->r[0] = L->r[low];              // Use the first record of the sublist to record the pivot
	keyType pivotKey = L->r[low].key; // Pivot record keywords are saved in pivotKey
	while (low < high) {              // Scanning alternately from the ends of the table to the middle
		while ((low < high) && (L->r[high].key >= pivotKey))
			--high;
		L->r[low] = L->r[high];       // Move records smaller than the pivot record to the low end
		while ((low < high) && (L->r[low].key <= pivotKey))
			++low;
		L->r[high] = L->r[low];       // Move records larger than the pivot record to the high end
	}
	L->r[low] = L->r[0];              // Pivot record in place
	return low;
}

// Initial value before calling: low=1; high=L->leghth;
// Do a quick sort of the subsequence r of the sequential list L
void QSort(sqList *L, int low, int high) {
	if (low < high) {                           // Length is greater than 1
		int pivotLoc = partition(L, low, high); // Split r[low..high] into two, pivotLoc is the pivot position
		QSort(L, low, pivotLoc - 1);            // Recursively sort the left sublist
		QSort(L, pivotLoc + 1, high);           // Recursively sort the right sublist
	}
}

// Do a quick sort of the sequential list L
void quickSort(sqList *L) {
	QSort(L, 1, L->length);
}


// Do a simple selection sort of the sequential list L
void selectSort(sqList *L) {
	for (int i = 1; i <= L->length; ++i) { // Select the record with the smallest keyword in L->r[i..L->length]
		int  min = i;
		for (int j = i; j < L->length; ++j)
			if (L->r[j].key < L->r[min].key)
				min = j;                   // min points to the record with the smallest keyword in this sorting
		if (min != i) {
			redType tmp = L->r[i];
			L->r[i] = L->r[min];
			L->r[min] = tmp;               // Exchange r[i] and r[tmp]
		}
	}
}


// Assuming that r[s+1..m] is already a heap, adjust r[s..m] to a large root heap rooted at r[s]
void heapAdjust(sqList *L, int s, int m) {
	bool flag = true;
	redType rc = L->r[s];
	for (int i = 2 * s; i <= m && flag; i *= 2) { // Filter down the node with a large key
		if ((i < m) && (L->r[i].key < L->r[i + 1].key))
			++i;                                  // i is the subscript of the record with a large key
		if (rc.key >= L->r[i].key)
			flag = false;                         // rc should be inserted in position s
		else {
			L->r[s] = L->r[i];
			s = i;
		}
	}
	L->r[s] = rc;                                 // Insert
}

// Construct the unordered sequence L->r[1..n] into a large root heap
void createHeap(sqList *L) {
	for (int i = L->length / 2; i; --i)
		heapAdjust(L, i, L->length); // Call heapAdjust repeatedly
}

// Do a heap sort of the sequential list L
void heapSort(sqList *L) {
	createHeap(L);               // Construct the unordered sequence L->r[1..L->length] into a large root heap
	for (int i = L->length; i > 1; --i) {
		int tmp = L->r[1];       // Interchanging the top record with the last record in the current unsorted subsequence L->r[1..i]
		L->r[1] = L->r[i];
		L->r[i] = tmp;
		heapAdjust(L, 1, i - 1); // Re-adjust L->r[1..i-1] to a large root stack
	}
}


// Merge the ordered list R[low..mid] and R[mid+1..high] into an ordered list T[low..high]
void merge(redType R[], redType T[], int low, int mid, int high) {
	int i = low, j = mid + 1, k = low;
	while (i <= mid && j <= high) // Incorporate records from R into T from small to large
		if (R[i].key <= R[j].key)
			T[k++] = R[i++];
		else
			T[k++] = R[j++];
	while (i <= mid)
		T[k++] = R[i++];          // Copy the remaining R[i..mid] to T
	while (j <= high)
		T[k++] = R[j++];          // Copy the remaining R[j..high] to T
}

// Merging sort R[low..high] and put it into T[low..high].
void MSort(redType R[], redType T[], int low, int high) {
	if (low == high)
		T[low] = R[low];
	else {
		int mid = (low + high) / 2;  // Split the current sequence into two and find the split point mid
		redType S[MAXSIZE + 1];
		MSort(R, S, low, mid);       // Recursively sort the subsequence R[low..mid] and put the result into S[low..mid]
		MSort(R, S, mid + 1, high);  // Recursively sort the subsequence R[mid+1..high] and put the result into S[mid+1..high]
		merge(S, T, low, mid, high); // Merge S[low..mid] and S[mid+1..high] into T[low..high]
	}
}

// Do a merging sort of the sequential list L
void mergeSort(sqList *L) {
	MSort(L->r, L->r, 1, L->length);
}