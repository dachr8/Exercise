class Solution {
    public int findLengthOfLCIS(int[] nums) {
        int ans = 0, anchor = 0;
        for (int i = 0; i < nums.length; i++) {
            ans = Math.max(ans, i - anchor + 1);
            if (i != nums.length - 1 && nums[i] >= nums[i + 1])
                anchor = i + 1;
        }
        return ans;
    }
}