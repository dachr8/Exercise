//69. Sqrt(x)
int mySqrt(int x) {
    if (!x)
        return 0;
    int left = 1, right = x, mid;
    while (true) {
        mid = (right + left) / 2;
        if (mid > x / mid)
            right = mid - 1;
        else {
            if (mid + 1 > x / (mid + 1))
                return mid;
            left = mid + 1;
        }
    }
}