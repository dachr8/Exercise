class Solution {
    public int peakIndexInMountainArray(int[] A) {
        int low = 1, high = A.length - 2;
        while (low < high) {
            int mid = low + (high - low) / 2;
            if (A[mid] < A[mid + 1])
                low = mid + 1;
            else
                high = mid;
        }
        return low;
    }
}