class Solution {
    public void moveZeroes(int[] nums) {
        for (int lastNonZeroFoundAt = 0, cur = 0; cur < nums.length; cur++)
            if (nums[cur] != 0) {
                int tmp = nums[lastNonZeroFoundAt];
                nums[lastNonZeroFoundAt] = nums[cur];
                nums[cur] = tmp;
                lastNonZeroFoundAt++;
            }
    }
}