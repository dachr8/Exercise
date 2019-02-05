class Solution {
    public int countPrimeSetBits(int L, int R) {
        int ans = 0;
        for (int i = L; i <= R; i++) {
            int x = Integer.bitCount(i);
            if (x == 2 || x == 3 || x == 5 || x == 7 || x == 11 || x == 13 || x == 17 || x == 19)
                ans++;
        }
        return ans;
    }
}