//278. First Bad Version
// Forward declaration of isBadVersion API.
bool isBadVersion(int version);

int firstBadVersion(int n) {
    int left = 1, right = n, mid;
    while (left < right) {
        mid = (right + left) / 2;
        if (isBadVersion(mid))
            right = mid;
        else
            left = mid + 1;
    }
    return left;
}
