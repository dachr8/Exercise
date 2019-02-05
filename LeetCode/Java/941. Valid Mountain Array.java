class Solution {
    public boolean validMountainArray(int[] A) {
        int N = A.length - 1;
        int i = 0;
        while (i < N && A[i] < A[i + 1])
            i++;
        if (i == 0 || i == N)
            return false;
        while (i < N && A[i] > A[i + 1])
            i++;
        return i == N;
    }
}