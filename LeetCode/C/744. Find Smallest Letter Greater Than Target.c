//744. Find Smallest Letter Greater Than Target
char nextGreatestLetter(char *letters, int lettersSize, char target) {
    int low = 0, high = lettersSize, mid;
    while (low < high) {
        mid = (high + low) / 2;
        if (letters[mid] > target)
            high = mid;
        else
            low = mid + 1;
    }

    return letters[low % lettersSize];
}
