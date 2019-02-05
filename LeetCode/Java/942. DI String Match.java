class Solution {
    public int[] diStringMatch(String S) {
        int N = S.length();
        int low = 0, high = N;
        int[] ans = new int[N + 1];
        for (int i = 0; i < N; i++)
            if (S.charAt(i) == 'I')
                ans[i] = low++;
            else
                ans[i] = high--;
        ans[N] = low;
        return ans;
    }
}