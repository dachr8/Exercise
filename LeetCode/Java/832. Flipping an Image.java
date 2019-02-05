class Solution {
    public int[][] flipAndInvertImage(int[][] A) {
        int N = A[0].length;
        for (int[] row : A)
            for (int i = 0; i < (N + 1) / 2; i++) {
                int tmp = row[i] ^ 1;
                row[i] = row[N - 1 - i] ^ 1;
                row[N - 1 - i] = tmp;
            }
        return A;
    }
}