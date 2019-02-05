class Solution {
    public int minDeletionSize(String[] A) {
        int ans = 0;
        int C = A[0].length(), R = A.length;
        for (int c = 0; c < C; c++)
            for (int r = 0; r < R - 1; r++)
                if (A[r].charAt(c) > A[r + 1].charAt(c)) {
                    ans++;
                    r = A.length - 1;
                }
        return ans;
    }
}