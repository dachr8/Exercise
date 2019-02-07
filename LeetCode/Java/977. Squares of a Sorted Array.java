class Solution {
    public int[] sortedSquares(int[] A) {
        int N = A.length;
        int[] ans = new int[N];
        int i = 0;
        int right = 0;
        while (right < N && A[right] < 0)
            right++;
        int left = right - 1;
        while (left >= 0 && right < N)
            if (A[left] * A[left] < A[right] * A[right])
                ans[i++] = A[left] * A[left--];
            else
                ans[i++] = A[right] * A[right++];
        while (left >= 0)
            ans[i++] = A[left] * A[left--];
        while (right < N)
            ans[i++] = A[right] * A[right++];
        return ans;
    }
}