class Solution {
    public int binaryGap(int N) {
        int last = -1, ans = 0;
        for (int i = 0; i < 32; i++)
            if (((N >> i) & 1) == 1) {
                if (last != -1)
                    ans = Math.max(ans, i - last);
                last = i;
            }
        return ans;
    }
}