class Solution {
    public int[] findErrorNums(int[] nums) {
        int dup = 0;
        for (int n : nums)
            if (nums[Math.abs(n) - 1] > 0)
                nums[Math.abs(n) - 1] *= -1;
            else
                dup = Math.abs(n);
        for (int i = 0; ; i++)
            if (nums[i] > 0)
                return new int[]{dup, i + 1};
    }
}