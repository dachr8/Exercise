class Solution {
    public List<List<Integer>> largeGroupPositions(String S) {
        List<List<Integer>> ans = new ArrayList();
        int N = S.length();
        int k = 0;
        for (int i = 0; i < N; i++)
            if (i == N - 1 || S.charAt(i) != S.charAt(i + 1)) {
                if (i - k + 1 >= 3)
                    ans.add(Arrays.asList(new Integer[]{k, i}));
                k = i + 1;
            }
        return ans;
    }
}