//746. Min Cost Climbing Stairs
int maxSubArray(int *nums, int numsSize) {
    int dp[numsSize], max = nums[0];
    dp[0] = nums[0];
    for (int i = 1; i < numsSize; i++) {
        dp[i] = nums[i] + (dp[i - 1] > 0 ? dp[i - 1] : 0);
        max = max > dp[i] ? max : dp[i];
    }
    return max;
}
