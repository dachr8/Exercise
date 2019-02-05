class Solution {
    public int countBinarySubstrings(String s) {
        int ans = 0, prev = 0, cur = 1;
        for (int i = 0; i < s.length() - 1; i++)
            if (s.charAt(i) == s.charAt(i + 1))
                cur++;
            else {
                ans += Math.min(prev, cur);
                prev = cur;
                cur = 1;
            }
        return ans + Math.min(prev, cur);
    }
}