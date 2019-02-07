class Solution {
    public int[] sumEvenAfterQueries(int[] A, int[][] queries) {
        int N = queries.length;
        int[] ans = new int[N];
        int S = 0;
        for (int x : A)
            if (x % 2 == 0)
                S += x;
        for (int i = 0; i < N; i++) {
            int index = queries[i][1];
            if (A[index] % 2 == 0)
                S -= A[index];
            A[index] += queries[i][0];
            if (A[index] % 2 == 0)
                S += A[index];
            ans[i] = S;
        }
        return ans;
    }
}